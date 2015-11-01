#include "videoplayer.h"

#include <glib.h>

#include "videoplayer_p.h"
#include "videoframe_p.h"
#include "thumbnailer.h"

static const char *VIDEO_OUTPUT_TYPE = "RV32";
typedef guint32 * PixelDepthType;

G_DEFINE_TYPE(VideoPlayer, video_player, G_TYPE_OBJECT)
static void video_player_init(VideoPlayer *self);
static void video_player_class_init(VideoPlayerClass *klass);
static void video_player_dispose(GObject *video_player);
static void video_player_finalize(GObject *video_player);

static void *vlc_video_lock_callback(void *data, void **frame_buffer_out)
{
    VideoPlayer *self = (VideoPlayer *)data;
    gsize buffer_size = 0;

    g_mutex_lock(&self->frame_.mutex_);

    buffer_size = self->video_data_.width_ *
                  self->video_data_.height_ *
                  sizeof(PixelDepthType);

    if (self->frame_.last_frame_)
        g_object_unref(self->frame_.last_frame_);

    self->frame_.last_frame_ = VIDEO_FRAME(g_object_new(VIDEO_FRAME_TYPE, NULL));
    self->frame_.last_frame_->buffer_ = (FrameBufferType)g_malloc(buffer_size);
    self->frame_.last_frame_->buffer_size_ = buffer_size;
    self->frame_.last_frame_->width_ = self->video_data_.width_;
    self->frame_.last_frame_->height_ = self->video_data_.height_;

    *frame_buffer_out = self->frame_.last_frame_->buffer_;

    return NULL;
}

static void vlc_video_unlock_callback(void *data, void *id, void *const *frame_buffer_in)
{
    VideoPlayer *self = (VideoPlayer *)data;

    UNUSED(id)
    UNUSED(frame_buffer_in)

    if (self->callbacks_.render_cb_)
        self->callbacks_.render_cb_(self->frame_.last_frame_,
                                    self->callbacks_.callback_data_);

    g_mutex_unlock(&self->frame_.mutex_);
}

static void vlc_video_frame_display(void *data, void *id)
{
    UNUSED(data)
    UNUSED(id)
}

static void vlc_event_callback(const libvlc_event_t *event, void *data)
{
    VideoPlayer *self = (VideoPlayer *)data;

    g_mutex_lock(&self->callbacks_.mutex_);

    switch (event->type)
    {
    default:
        break;

    case libvlc_MediaPlayerPositionChanged:
        if (self->callbacks_.pos_changed_cb_)
            self->callbacks_.pos_changed_cb_(event->u.media_player_position_changed.new_position,
                                             self->callbacks_.callback_data_);
    }

    g_mutex_unlock(&self->callbacks_.mutex_);
}

VideoPlayer *video_player_new()
{
    VideoPlayer *self = VIDEO_PLAYER(g_object_new(VIDEO_PLAYER_TYPE, NULL));

    g_mutex_init(&self->callbacks_.mutex_);
    self->callbacks_.callback_data_ = NULL;
    self->callbacks_.render_cb_ = NULL;
    self->callbacks_.pos_changed_cb_ = NULL;
    g_mutex_init(&self->frame_.mutex_);
    self->frame_.last_frame_ = NULL;
    self->video_data_.vlc_media_player_ = NULL;
    self->video_data_.vlc_event_mgr_ = NULL;
    self->video_data_.width_ = 0;
    self->video_data_.height_ = 0;
    self->video_data_.volume_ = 100;

    return self;
}

static void video_player_init(VideoPlayer *self)
{
    const char *const vlc_args[] = {
        "-I", "dummy",
        "--ignore-config",
        "--no-xlib",
        "--no-sub-autodetect-file",
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

    if (self->video_data_.vlc_instance_)
        libvlc_release(self->video_data_.vlc_instance_);
    if (self->video_data_.vlc_media_player_)
        libvlc_media_player_release(self->video_data_.vlc_media_player_);

    G_OBJECT_CLASS(video_player_parent_class)->finalize(video_player);
}

void video_player_ref(VideoPlayer *self)
{
    g_object_ref(self);
}

void video_player_unref(VideoPlayer *self)
{
    g_object_unref(self);
}

void video_player_set_callback_data(VideoPlayer *self, gpointer callback_data)
{
    self->callbacks_.callback_data_ = callback_data;
}

void video_player_set_render_callback(VideoPlayer *self, RenderCallback cb)
{
    self->callbacks_.render_cb_ = cb;
}

void video_player_set_position_changed_callback(VideoPlayer *self, PositionChangedCallback cb)
{
    self->callbacks_.pos_changed_cb_ = cb;
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

#ifdef WINNT
    gchar **split_path = g_strsplit(path, "/", 0);
    gchar *win_path = g_strjoinv("\\\\", split_path);
    g_strfreev(split_path);

    media = libvlc_media_new_path(vlc_instance, win_path);

    g_free(win_path);
#else
    media = libvlc_media_new_path(vlc_instance, path);
#endif
    g_return_if_fail(media != NULL);
    libvlc_media_parse(media);

    track_info_size = libvlc_media_get_tracks_info(media, &track_info);

    for (i = 0; i < track_info_size; ++i)
        if (track_info[i].i_type == libvlc_track_video)
        {
            self->video_data_.width_ = track_info[i].u.video.i_width;
            self->video_data_.height_ = track_info[i].u.video.i_height;

            break;
        }

    g_free(track_info);

    if (!media_player)
    {
        self->video_data_.vlc_media_player_ = libvlc_media_player_new_from_media(media);
        self->video_data_.vlc_event_mgr_ =
                libvlc_media_player_event_manager(self->video_data_.vlc_media_player_);

        video_player_private_set_callbacks(self);
        video_player_private_update_format(self);
    }
    else
        libvlc_media_player_set_media(self->video_data_.vlc_media_player_, media);

    libvlc_media_release(media);
}

void video_player_set_size(VideoPlayer *self, const guint16 width, const guint16 height)
{
    self->video_data_.width_ = width;
    self->video_data_.height_ = height;

    video_player_private_update_format(self);
}

void video_player_play(VideoPlayer *self)
{
    libvlc_media_player_play(self->video_data_.vlc_media_player_);
}

void video_player_pause(VideoPlayer *self)
{
    libvlc_media_player_pause(self->video_data_.vlc_media_player_);
}

void video_player_stop(VideoPlayer *self)
{
    libvlc_media_player_stop(self->video_data_.vlc_media_player_);
}

void video_player_set_position(VideoPlayer *self, const gfloat position)
{
    libvlc_media_player_set_position(self->video_data_.vlc_media_player_, position);
}

void video_player_set_time(VideoPlayer *self, const gint64 position)
{
    libvlc_media_player_set_time(self->video_data_.vlc_media_player_, position);
}

gint64 video_player_get_current_time(VideoPlayer *self)
{
    return libvlc_media_player_get_time(self->video_data_.vlc_media_player_);
}

gint64 video_player_get_duration(VideoPlayer *self)
{
    return libvlc_media_player_get_length(self->video_data_.vlc_media_player_);
}

void video_player_set_volume(VideoPlayer *self, guint8 volume)
{
    self->video_data_.muted_ = FALSE;
    self->video_data_.volume_ = volume > 100 ? 100 : volume;

    libvlc_audio_set_volume(self->video_data_.vlc_media_player_,
                            self->video_data_.volume_);
}

void video_player_set_muted(VideoPlayer *self, gboolean muted)
{
    libvlc_audio_set_volume(self->video_data_.vlc_media_player_,
                            muted ? 0 : self->video_data_.volume_);
    self->video_data_.muted_ = muted;
}

void video_player_private_update_format(VideoPlayer *self)
{
    if (self->video_data_.vlc_media_player_)
        libvlc_video_set_format(self->video_data_.vlc_media_player_,
                                VIDEO_OUTPUT_TYPE,
                                self->video_data_.width_,
                                self->video_data_.height_,
                                self->video_data_.width_ * 4);
}

void video_player_private_set_callbacks(VideoPlayer *self)
{
    libvlc_event_attach(self->video_data_.vlc_event_mgr_,
                        libvlc_MediaPlayerPositionChanged,
                        vlc_event_callback,
                        self);

    libvlc_video_set_callbacks(self->video_data_.vlc_media_player_,
                               vlc_video_lock_callback,
                               vlc_video_unlock_callback,
                               vlc_video_frame_display,
                               self);
}

/* Static methods */
VideoFrame *video_player_generate_thumbnail(const gchar *video_path,
                                            const gfloat position,
                                            const guint16 width,
                                            const guint16 height)
{
    Thumbnailer *thumbnailer = thumbnailer_new();
    thumbnailer_set_source(thumbnailer, video_path);
    thumbnailer_set_size(thumbnailer, width, height);
    thumbnailer_set_position(thumbnailer, position);

    VideoFrame *thumbnail = thumbnailer_generate_thumbnail(thumbnailer);

    g_object_unref(thumbnailer);

    return thumbnail;
}
