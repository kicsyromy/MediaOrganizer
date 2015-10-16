#include "videoplayer.h"

C_STYLE_BEGIN

#include <glib.h>
#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>

#include "videoframe.h"
#include "videoframe_p.h"

/* Every frame will be renderd in 32bit bitmap format */
static const char *VIDEO_OUTPUT_TYPE = "RV32";
typedef guint32 * PixelDepthType;

struct Frame
{
    GMutex mutex_;
    VideoFrame *last_frame_;
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
static void video_player_dispose(GObject *video_player);
static void video_player_finalize(GObject *video_player);

/* Private methods */
static void video_player_update_format(VideoPlayer *self);

static void *vlc_video_lock_callback(void *data, void **frame_buffer_out)
{
    VideoPlayer *self = (VideoPlayer *)data;
    gsize buffer_size = 0;

    g_mutex_lock(&self->frame_.mutex_);

    buffer_size = self->video_data_.width *
                  self->video_data_.height *
                  sizeof(PixelDepthType);

    if (self->frame_.last_frame_)
        g_object_unref(self->frame_.last_frame_);

    self->frame_.last_frame_ = VIDEO_FRAME(g_object_new(VIDEO_FRAME_TYPE, NULL));
    self->frame_.last_frame_->buffer_ = (FrameBufferType)g_malloc(buffer_size);
    self->frame_.last_frame_->buffer_size_ = buffer_size;
    self->frame_.last_frame_->width_ = self->video_data_.width;
    self->frame_.last_frame_->height_ = self->video_data_.height;

    *frame_buffer_out = self->frame_.last_frame_->buffer_;

    return NULL;
}

static void vlc_video_unlock_callback(void *data, void *id, void *const *frame_buffer_in)
{
    VideoPlayer *self = (VideoPlayer *)data;

    UNUSED(id)
    UNUSED(frame_buffer_in)

    self->cb_(self->frame_.last_frame_,
              self->video_data_.width,
              self->video_data_.height,
              self->cb_data_);

    g_mutex_unlock(&self->frame_.mutex_);
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
    self->frame_.last_frame_ = NULL;
    self->video_data_.vlc_media_player_ = NULL;

    return self;
}

static void video_player_init(VideoPlayer *self)
{
    const char *const vlc_args[] = {
        "-I", "dummy",
        "--ignore-config",
        "--no-xlib",
        "--no-sub-autodetect-file",
        "--no-inhibit",
        "--no-disable-screensaver",
        "--no-snapshot-preview",
        "--no-stats"
    };

    self->video_data_.vlc_instance_ = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
}

static void video_player_class_init(VideoPlayerClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = video_player_finalize;
    G_OBJECT_CLASS(klass)->dispose = video_player_dispose;
}

static void video_player_dispose(GObject *video_player)
{
    VideoPlayer *self = VIDEO_PLAYER(video_player);

    g_clear_object(&self->frame_.last_frame_);

    G_OBJECT_CLASS(video_player_parent_class)->dispose(video_player);
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
    libvlc_instance_t *vlc_instance = self->video_data_.vlc_instance_;
    libvlc_media_player_t *media_player = self->video_data_.vlc_media_player_;

    libvlc_media_t *media = NULL;
    libvlc_media_track_info_t *track_info = NULL;
    int track_info_size = 0;
    int i = 0;

    if (media_player && libvlc_media_player_is_playing(media_player))
        libvlc_media_player_stop(media_player);

    media = libvlc_media_new_path(vlc_instance, path);
    libvlc_media_parse(media);

    track_info_size = libvlc_media_get_tracks_info(media, &track_info);

    for (i = 0; i < track_info_size; ++i)
        if (track_info[i].i_type == libvlc_track_video)
        {
            self->video_data_.width = track_info[i].u.video.i_width;
            self->video_data_.height = track_info[i].u.video.i_height;

            break;
        }

    g_free(track_info);

    if (!media_player)
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
    UNUSED(self)
    UNUSED(volume)
}

void video_player_set_muted(VideoPlayer *self, int muted)
{
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

/* Static methods */
int video_player_generate_thumbnail(const gchar *video_path,
                                    const gchar *thumbnail_path,
                                    const gfloat position,
                                    const guint16 width,
                                    const guint16 height)
{
    gfloat pos = (position > 1) ? 1 : (position < 0) ? 0 : position;
    libvlc_instance_t *vlc_instance = NULL;
    libvlc_media_t *media = NULL;
    libvlc_media_player_t *media_player = NULL;
    int return_value = 0;

    static const char* const args[] = {
        "--intf", "dummy",
        "--vout", "dummy",
        "--no-audio",
        "--no-video-title-show",
        "--no-stats",
        "--no-sub-autodetect-file",
        "--no-inhibit",
        "--no-disable-screensaver",
        "--no-snapshot-preview",
        "--verbose=2"
    };

    vlc_instance = libvlc_new(sizeof args / sizeof *args, args);
    media = libvlc_media_new_path(vlc_instance, video_path);
    media_player = libvlc_media_player_new_from_media(media);

    libvlc_media_player_play(media_player);
    libvlc_media_player_set_position(media_player, pos);
    return_value = libvlc_video_take_snapshot(media_player, 0, thumbnail_path, width, height);
    libvlc_media_player_stop(media_player);

    libvlc_media_release(media);
    libvlc_media_player_release(media_player);
    libvlc_release(vlc_instance);

    return return_value;
}

C_STYLE_END

