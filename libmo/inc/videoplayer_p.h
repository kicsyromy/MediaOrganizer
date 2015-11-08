#ifndef VIDEOPLAYER_P_H
#define VIDEOPLAYER_P_H

#include <mo_global.h>

C_STYLE_BEGIN

#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>
#include <vlc/libvlc_events.h>

#include "videoplayer.h"

/* Every frame will be renderd in 32bit bitmap format */

struct Frame
{
    GMutex mutex_;
    VideoFrame *last_frame_;
};

struct VideoData
{
    libvlc_instance_t *vlc_instance_;
    libvlc_media_player_t *vlc_media_player_;
    libvlc_event_manager_t *vlc_event_mgr_;

    gint16 width_;
    gint16 height_;

    guint8 volume_;
    gboolean muted_;
};

struct CallbackData
{
    gpointer render_cb_data_;
    gpointer pos_changed_cb_data_;
};

struct Callbacks
{
    GMutex mutex_;
    RenderCallback render_cb_;
    PositionChangedCallback pos_changed_cb_;
    struct CallbackData cb_data_;
};

struct _VideoPlayer
{
    GObject parent;

    /* Members */
    struct Callbacks callbacks_;
    struct Frame frame_;
    struct VideoData video_data_;
};

struct _VideoPlayerClass
{
    GObjectClass parent;
};

void video_player_private_update_format(VideoPlayer *self);
void video_player_private_set_callbacks(VideoPlayer *self);

C_STYLE_END

#endif // VIDEOPLAYER_P_H
