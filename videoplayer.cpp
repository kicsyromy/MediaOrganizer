#include "videoplayer.h"

C_STYLE_BEGIN

#include <glib.h>
#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>

#define G_CLASS(klass)  G_TYPE_CHECK_CLASS_CAST((klass), G_TYPE_OBJECT, GObjectClass)

static const char *VIDEO_OUTPUT_TYPE = "RV32";
typedef guint32 * ActualPixelDepthType;

struct Frame
{
    GMutex mutex_;
    /* Every frame will be renderd in 32bit bitmap format */
    PixelDepthType buffer_;
};

struct VideoData
{
    libvlc_instance_t *vlc_instance_;
    libvlc_media_player_t *vlc_media_player_;

    gint16 width;
    gint16 height;
};

struct _VideoPlayer
{
    GObject parent;

    /* Members */
    RenderCallback cb_;
    gpointer cb_data_;
    struct Frame frame_;
    struct VideoData video_data_;
};

struct _VideoPlayerClass
{
    GObjectClass parent;
};

G_DEFINE_TYPE(VideoPlayer, video_player, G_TYPE_OBJECT)
static void video_player_init(VideoPlayer *self);
static void video_player_class_init(VideoPlayerClass *klass);
static void video_player_finalize(GObject *video_player);


/* Private methods */
static void video_player_update_format(VideoPlayer *self);

static void *vlc_video_lock_callback(void *data, void **frame_buffer_out)
{
    VideoPlayer *self = (VideoPlayer *)data;
    g_mutex_lock(&self->frame_.mutex_);

    self->frame_.buffer_ = (PixelDepthType)g_malloc(self->video_data_.width *
                                               self->video_data_.height *
                                               sizeof(ActualPixelDepthType));

    *frame_buffer_out = self->frame_.buffer_;

    return NULL; /* picture identifier */
}

static void vlc_video_unlock_callback(void *data, void *id, void *const *frame_buffer_in)
{
    UNUSED(id)
    UNUSED(frame_buffer_in)

    VideoPlayer *self = (VideoPlayer *)data;
    g_mutex_unlock(&self->frame_.mutex_);

    self->cb_(self->frame_.buffer_,
              self->video_data_.width,
              self->video_data_.height,
              self->cb_data_);
}

static void vlc_video_frame_display(void *data, void *id)
{
    UNUSED(data)
    UNUSED(id)
}

VideoPlayer *video_player_new()
{
    VideoPlayer *self = VIDEO_PLAYER(g_object_new(VIDEO_PLAYER_TYPE, NULL));

    self->cb_ = NULL;
    self->cb_data_ = NULL;
    self->frame_.buffer_ = NULL;
    self->video_data_.vlc_media_player_ = NULL;

    return self;
}

static void video_player_init(VideoPlayer *self)
{
    const char *const vlc_args[] = {
        "-I", "dummy", // Don't use any interface
        "--ignore-config", // Don't use VLC's config
        "--no-audio", /* skip any audio track */
        "--no-xlib", /* tell VLC to not use Xlib */
//        "--extraintf=logger",     // Log anything
//        "--verbose=2",            // Be verbose
    };

    self->video_data_.vlc_instance_ = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
}

static void video_player_class_init(VideoPlayerClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = video_player_finalize;
}

static void video_player_finalize(GObject *video_player)
{
    VideoPlayer *self = VIDEO_PLAYER(video_player);

    libvlc_release(self->video_data_.vlc_instance_);
    libvlc_media_player_release(self->video_data_.vlc_media_player_);

    G_OBJECT_CLASS(video_player_parent_class)->finalize(video_player);
}

void video_player_set_callback(VideoPlayer *self, RenderCallback cb, gpointer callback_data)
{
    self->cb_ = cb;
    self->cb_data_ = callback_data;
}

void video_player_set_source(VideoPlayer *self, const gchar *path)
{
    libvlc_media_t *media = libvlc_media_new_location(self->video_data_.vlc_instance_, path);

    if (!self->video_data_.vlc_media_player_)
    {
        self->video_data_.vlc_media_player_ = libvlc_media_player_new_from_media(media);

        libvlc_video_set_callbacks(self->video_data_.vlc_media_player_,
                                   vlc_video_lock_callback,
                                   vlc_video_unlock_callback,
                                   vlc_video_frame_display,
                                   self);

        video_player_update_format(self);
    }
    else
        libvlc_media_player_set_media(self->video_data_.vlc_media_player_, media);

    libvlc_media_release(media);
}

void video_player_set_size(VideoPlayer *self, guint16 width, guint16 height)
{
    self->video_data_.width = width;
    self->video_data_.height = height;

    video_player_update_format(self);
}

void video_player_play(VideoPlayer *self)
{
    libvlc_media_player_play(self->video_data_.vlc_media_player_);
}

void video_player_pause(VideoPlayer *self)
{
    libvlc_media_player_pause(self->video_data_.vlc_media_player_);
}

void video_player_set_position(VideoPlayer *self, const gint64 position)
{
    libvlc_media_player_set_time(self->video_data_.vlc_media_player_, position);
}

void video_player_set_volume(VideoPlayer *self, const double volume)
{
    // Has something to do with some callbacks that I have no idea how to use
    // YET!
    UNUSED(self)
    UNUSED(volume)
}

void video_player_set_muted(VideoPlayer *self, bool muted)
{
    // Has something to do with some callbacks that I have no idea how to use
    // YET!
    UNUSED(self)
    UNUSED(muted)
}

gint64 video_player_get_duration(VideoPlayer *self)
{
    return libvlc_media_player_get_time(self->video_data_.vlc_media_player_);
}

static void video_player_update_format(VideoPlayer *self)
{
    if (self->video_data_.vlc_media_player_)
        libvlc_video_set_format(self->video_data_.vlc_media_player_,
                                VIDEO_OUTPUT_TYPE,
                                self->video_data_.width,
                                self->video_data_.height,
                                self->video_data_.width * 4);
}

C_STYLE_END

