#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <mo_global.h>

C_STYLE_BEGIN

#include <glib-object.h>

#define VIDEO_PLAYER_TYPE video_player_get_type()
#define VIDEO_PLAYER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), VIDEO_PLAYER_TYPE, VideoPlayer))

typedef struct _VideoPlayer         VideoPlayer;
typedef struct _VideoPlayerClass    VideoPlayerClass;

typedef void (*RenderCallback)(gint8 *frame_buffer, int width, int height, void *data);

MO_API  GType video_player_get_type();

/* Constructor and destructor */
MO_API  VideoPlayer *video_player_new();

/* Public methods */
MO_API  void video_player_set_callback(VideoPlayer *player, RenderCallback cb, void *callback_data);
MO_API  void video_player_set_source(VideoPlayer *player, const gchar *path);
MO_API  void video_player_play(VideoPlayer *player);
MO_API  void video_player_pause(VideoPlayer *player);
MO_API  void video_player_set_position(VideoPlayer *player, const gint64 position);
MO_API  void video_player_set_volume(VideoPlayer *player, const double volume);
MO_API  void video_player_set_muted(VideoPlayer *player, bool muted);
MO_API  gint64 video_player_get_duration(VideoPlayer *player);

/* Static methods */
//gsize video_player_generate_thumbnail(const char *path,
//                         const char *format,
//                         unsigned char *&buffer,
//                         const int offset);

C_STYLE_END

#endif // VIDEOPLAYER_H
