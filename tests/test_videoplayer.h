#ifndef TEST_VIDEOPLAYER_H
#define TEST_VIDEOPLAYER_H

#include <videoplayer.h>
#include <videoframe.h>

C_STYLE_BEGIN

typedef struct
{
    GMutex mutex_;
    GCond condition_;

    gfloat requested_pos_;
    gboolean position_ok_;
}
PositionHelper;

typedef struct
{
    VideoPlayer *player_;
    PositionHelper *pos_helper_;
}
VideoPlayerFixture;

void video_player_fixture_set_up(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_fixture_tear_down(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_init(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_set_video(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_set_size(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_play(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_pause(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_stop(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_test_set_position(VideoPlayerFixture *fixture, gconstpointer data);
void video_player_tests_add();

C_STYLE_END

#endif // TEST_VIDEOPLAYER_H
