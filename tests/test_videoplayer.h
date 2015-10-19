#ifndef TEST_VIDEOPLAYER_H
#define TEST_VIDEOPLAYER_H

#include <videoplayer.h>

C_STYLE_BEGIN

typedef struct
{
    VideoPlayer *player_;
}
VideoPlayerFixture;

void video_player_fixture_set_up_empty(VideoPlayerFixture *fixture);
void video_player_fixture_set_up_with_video(VideoPlayerFixture *fixture, const gchar *file_path);
void video_player_fixture_set_up_with_video_and_size(VideoPlayerFixture *fixture,
                                                     const gchar *file_path,
                                                     const guint16 width,
                                                     const guint16 height);
void video_player_fixture_tear_down(VideoPlayerFixture *fixture);

C_STYLE_END

#endif // TEST_VIDEOPLAYER_H
