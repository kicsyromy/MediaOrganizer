#include "thumbnailer.h"

#include <math.h>

#include "videoplayer.h"
#include "videoframe.h"

struct _Thumbnailer
{
    GObject parent;

    VideoPlayer *player_;
    VideoFrame *frame_;
    gfloat position_;
    GMutex render_mutex_;
    GMutex pos_ch_mutex_;
    GCond condition_;
    gboolean is_correct_position;
};

struct _ThumbnailerClass
{
    GObjectClass parent;
};

G_DEFINE_TYPE(Thumbnailer, thumbnailer, G_TYPE_OBJECT)
static void thumbnailer_init(Thumbnailer *self);
static void thumbnailer_class_init(ThumbnailerClass *klass);
static void thumbnailer_dispose(GObject *thumbnailer);

static void render_callback(VideoFrame *frame, gpointer data)
{
    Thumbnailer *self = (Thumbnailer *)data;

    g_mutex_lock(&self->render_mutex_);

    if (self->is_correct_position)
    {
        self->frame_ = video_frame_copy(frame);
        g_cond_signal(&self->condition_);
    }

    g_mutex_unlock(&self->render_mutex_);
}

static void position_changed_callback(gfloat new_position, gpointer data)
{
    Thumbnailer *self = (Thumbnailer *)data;

    g_mutex_lock(&self->pos_ch_mutex_);

    if (fabs(new_position - self->position_) < 0.01)
        self->is_correct_position = TRUE;

    g_mutex_unlock(&self->pos_ch_mutex_);
}

Thumbnailer *thumbnailer_new()
{
    Thumbnailer *self = THUMBNAILER(g_object_new(THUMBNAILER_TYPE, NULL));

    self->frame_ = NULL;
    self->position_ = 0.0;
    g_mutex_init(&self->render_mutex_);
    g_mutex_init(&self->pos_ch_mutex_);
    g_cond_init(&self->condition_);
    self->is_correct_position = FALSE;

    return self;
}

static void thumbnailer_init(Thumbnailer *self)
{
    self->player_ = video_player_new();
}

static void thumbnailer_class_init(ThumbnailerClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = thumbnailer_dispose;
}

static void thumbnailer_dispose(GObject *thumbnailer)
{
    g_clear_object(&(THUMBNAILER(thumbnailer)->player_));

    G_OBJECT_CLASS(thumbnailer_parent_class)->dispose(thumbnailer);
}

void thumbnailer_set_source(Thumbnailer *self, const gchar *path)
{
    video_player_set_source(self->player_, path);
}

void thumbnailer_set_size(Thumbnailer *self, const guint16 width, const guint16 height)
{
    video_player_set_size(self->player_, width, height);
}

void thumbnailer_set_position(Thumbnailer *self, const gfloat position)
{
    self->position_ = position <= 1.0 ? (position >= 0.0 ? position : 0.0) : 1.0;
}

VideoFrame *thumbnailer_generate_thumbnail(Thumbnailer *self)
{
    UNUSED(self)

    video_player_set_render_callback(self->player_, render_callback, self);
    video_player_set_position_changed_callback(self->player_, position_changed_callback, self);

    g_mutex_lock(&self->render_mutex_);

    video_player_set_muted(self->player_, TRUE);
    video_player_play(self->player_);
    video_player_set_position(self->player_, self->position_);

    while (!self->frame_)
        g_cond_wait(&self->condition_, &self->render_mutex_);

    g_mutex_unlock(&self->render_mutex_);

    return self->frame_;

    return NULL;
}
