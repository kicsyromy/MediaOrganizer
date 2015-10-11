#include "videoplayer.h"

C_STYLE_BEGIN

#include <glib.h>
#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>

struct Frame
{
    GMutex mutex_;
    gint8 *buffer_;
    size_t buffer_size_;
};

struct VideoData
{
    libvlc_instance_t *vlc_instance_;
    libvlc_media_player_t *vlc_media_player_;
};

struct _VideoPlayer
{
    GObject parent;

    /* Members */
    RenderCallback cb_;
    void *cb_data_;
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

static void video_pre_render_callback(void *video_player,
                                      gint8 **pixel_buffer,
                                      size_t size)
{
    VideoPlayer *self = (VideoPlayer *)video_player;
    g_mutex_lock(&self->frame_.mutex_);

    if (self->frame_.buffer_size_ != size)
    {
        self->frame_.buffer_size_ = size;

        self->frame_.buffer_ = !self->frame_.buffer_ ?
                    (gint8 *)g_malloc(size) :
                    (gint8 *)g_realloc(self->frame_.buffer_, size);
    }

    *pixel_buffer = self->frame_.buffer_;
}

static void video_post_render_callback(void *video_player,
                                      gint8 *pixel_buffer,
                                      int width,
                                      int height,
                                      int pixel_pitch,
                                      size_t size,
                                      gint64 pts)
{
    UNUSED(pixel_buffer)
    UNUSED(pixel_pitch)
    UNUSED(size)
    UNUSED(pts)

    VideoPlayer *self = (VideoPlayer *)video_player;

    if (self->cb_)
        self->cb_(self->frame_.buffer_, width, height, self->cb_data_);

    g_mutex_unlock(&self->frame_.mutex_);
}


static void audio_prerender_callback(void *audio_data,
                            uint8_t **pcm_buffer,
                            size_t size)
{
    *pcm_buffer = (uint8_t *)g_malloc(size);
}

static void audio_postrender_callback(void *audio_data,
                             uint8_t *pcm_buffer,
                             unsigned int channels,
                             unsigned int rate,
                             unsigned int nb_samples,
                             unsigned int bits_per_sample,
                             size_t size,
                             int64_t pts)
{
    UNUSED(audio_data)
    UNUSED(pcm_buffer)
    UNUSED(channels)
    UNUSED(rate)
    UNUSED(nb_samples)
    UNUSED(bits_per_sample)
    UNUSED(size)
    UNUSED(pts)
}

VideoPlayer *video_player_new()
{
    VideoPlayer *self = VIDEO_PLAYER(g_object_new(VIDEO_PLAYER_TYPE, NULL));

    self->cb_ = NULL;
    self->cb_data_ = NULL;
    self->frame_.buffer_size_ = 0;
    self->frame_.buffer_ = NULL;

    const int smem_options_size = 1000;
    char smem_options[smem_options_size];
    snprintf(smem_options,
             smem_options_size,
             "#transcode{vcodec=RV24,acodec=in24}:smem{"
             "video-prerender-callback=%lld,"
             "video-postrender-callback=%lld,"
             "audio-prerender-callback=%lld,"
             "audio-postrender-callback=%lld,"
             "video-data=%lld,"
             "no-time-sync},",
             (long long int)(intptr_t)(void *)&video_pre_render_callback,
             (long long int)(intptr_t)(void *)&video_post_render_callback,
             (long long int)(intptr_t)(void *)&audio_prerender_callback,
             (long long int)(intptr_t)(void *)&audio_postrender_callback,
             (long long int)(intptr_t)(void *)&self->frame_);

    const char *const vlc_args[] = {
        "-I", "dummy", // Don't use any interface
        "--ignore-config", // Don't use VLC's config
//        "--extraintf=logger",     // Log anything
//        "--verbose=2",            // Be verbose
        "--sout", smem_options // Stream to memory
    };

    self->video_data_.vlc_instance_ = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    self->video_data_.vlc_media_player_ = NULL;

    return self;
}

static void video_player_init(VideoPlayer *self)
{
    // The fuck is the point of this function???
    UNUSED(self)
}

static void video_player_class_init(VideoPlayerClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = video_player_dispose;
}

static void video_player_dispose(GObject *video_player)
{
    VideoPlayer *self = VIDEO_PLAYER(video_player);

    libvlc_release(self->video_data_.vlc_instance_);
    libvlc_media_player_release(self->video_data_.vlc_media_player_);

    g_free(self->frame_.buffer_);

    // Explicitly call parent's dispose aswell
    VideoPlayerClass *klass = (VideoPlayerClass *)G_OBJECT_GET_CLASS(video_player);
    klass->parent.dispose(video_player);
}

void video_player_set_callback(VideoPlayer *self, RenderCallback cb, void *callback_data)
{
    self->cb_ = cb;
    self->cb_data_ = callback_data;
}

void video_player_set_source(VideoPlayer *self, const gchar *path)
{
    libvlc_media_t *media = libvlc_media_new_location(self->video_data_.vlc_instance_, path);

    if (!self->video_data_.vlc_media_player_)
        self->video_data_.vlc_media_player_ = libvlc_media_player_new_from_media(media);
    else
        libvlc_media_player_set_media(self->video_data_.vlc_media_player_, media);

    libvlc_media_release(media);
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

C_STYLE_END
