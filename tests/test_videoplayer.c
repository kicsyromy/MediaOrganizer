#include "test_videoplayer.h"

#include "test_global.h"
#include "videoplayer_p.h"

void video_player_fixture_set_up(VideoPlayerFixture *fixture, gconstpointer data)
{
    UNUSED(data)

    fixture->player_ = video_player_new();
}

void video_player_fixture_tear_down(VideoPlayerFixture *fixture, gconstpointer data)
{
    UNUSED(data)

    g_object_unref(fixture->player_);
}

void video_player_test_init(VideoPlayerFixture *fixture, gconstpointer data)
{
    UNUSED(data)

    VideoPlayer *player = fixture->player_;

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);
    TEST_IS_NULL(player->frame_.last_frame_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width, ==, 0);
    TEST_CMPINT(player->video_data_.height, ==, 0);

    END_TEST_CASE
}

void video_player_test_init_with_video(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const gchar *video_path = (const gchar *)data;

    g_print("\nVIDEO: %s\n", video_path);

    video_player_set_source(player, video_path);

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);
    TEST_IS_NULL(player->frame_.last_frame_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width, ==, 640);
    TEST_CMPINT(player->video_data_.height, ==, 360);

    END_TEST_CASE
}

void video_player_tests_add()
{
    GString *video_path = g_string_new(TEST_DATA_PATH);
    g_string_append(video_path, "big_buck_bunny.mp4");

    g_test_add("/video_player/test_initialization", VideoPlayerFixture, NULL,
               video_player_fixture_set_up, video_player_test_init,
               video_player_fixture_tear_down);

    g_test_add("/video_player/test_initialization_with_video", VideoPlayerFixture, video_path->str,
               video_player_fixture_set_up, video_player_test_init_with_video,
               video_player_fixture_tear_down);
}

