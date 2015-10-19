#ifndef TEST_VIDEOPLAYER_H
#define TEST_VIDEOPLAYER_H

#include <videoplayer.h>

C_STYLE_BEGIN

typedef struct
{
    VideoPlayer *player_;
}
VideoPlayerFixture;

void video_player_fixture_set_up(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_fixture_tear_down(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_init(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_init_with_video(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_tests_add();

C_STYLE_END

#endif // TEST_VIDEOPLAYER_H
