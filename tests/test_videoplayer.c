#include "test_videoplayer.h"

#include "test_global.h"
#include "videoplayer_p.h"
#include "videoframe_p.h"

static const guint16 default_video_width = 640;
static const guint16 default_video_height = 360;

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
    TEST_CMPINT(player->video_data_.width_, ==, 0);
    TEST_CMPINT(player->video_data_.height_, ==, 0);

    END_TEST_CASE
}

void video_player_test_set_video(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const gchar *video_path = (const gchar *)data;

    video_player_set_source(player, video_path);

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);
    TEST_IS_NULL(player->frame_.last_frame_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width_, ==, default_video_width);
    TEST_CMPINT(player->video_data_.height_, ==, default_video_height);

    END_TEST_CASE
}

void video_player_test_set_size(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const guint16 video_width = 300;
    const guint16 video_height = 200;
    const gchar *video_path = (const gchar *)data;

    video_player_set_source(player, video_path);
    video_player_set_size(player, video_width, video_height);

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);
    TEST_IS_NULL(player->frame_.last_frame_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width_, ==, video_width);
    TEST_CMPINT(player->video_data_.height_, ==, video_height);

    END_TEST_CASE

}

void video_player_test_play(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const gchar *video_path = (const gchar *)data;

    video_player_set_source(player, video_path);
    video_player_play(player);

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);
    g_usleep(0.5 * G_USEC_PER_SEC);
    TEST_IS_NOT_NULL(player->frame_.last_frame_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width_, ==, default_video_width);
    TEST_CMPINT(player->video_data_.height_, ==, default_video_height);

    END_TEST_CASE
}

void video_player_test_pause(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const gchar *video_path = (const gchar *)data;

    video_player_set_source(player, video_path);
    video_player_play(player);

    BEGIN_TEST_CASE

    TEST_IS_NULL(player->callbacks_.callback_data_);
    TEST_IS_NULL(player->callbacks_.render_cb_);
    TEST_IS_NULL(player->callbacks_.pos_changed_cb_);

    g_usleep(0.5 * G_USEC_PER_SEC);
    video_player_pause(player);
    VideoFrame *after_pause = video_frame_copy(player->frame_.last_frame_);
    g_usleep(0.5 * G_USEC_PER_SEC);
    VideoFrame *after_sleep = video_frame_copy(player->frame_.last_frame_);

    TEST_IS_TRUE(video_frame_equals(after_pause, after_sleep));
    TEST_IS_NOT_NULL(player->video_data_.vlc_instance_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_media_player_);
    TEST_IS_NOT_NULL(player->video_data_.vlc_event_mgr_);
    TEST_CMPINT(player->video_data_.width_, ==, default_video_width);
    TEST_CMPINT(player->video_data_.height_, ==, default_video_height);

    END_TEST_CASE
}

void video_player_test_stop(VideoPlayerFixture *fixture, gconstpointer data)
{
    VideoPlayer *player = fixture->player_;
    const gchar *video_path = (const gchar *)data;

    video_player_set_source(player, video_path);
}

void video_player_tests_add()
{
    GString *video_path = g_string_new(TEST_DATA_PATH);
    g_string_append(video_path, "big_buck_bunny.mp4");

    g_test_add("/video_player/test_initialization", VideoPlayerFixture, NULL,
               video_player_fixture_set_up, video_player_test_init,
               video_player_fixture_tear_down);

    g_test_add("/video_player/test_set_video", VideoPlayerFixture, video_path->str,
               video_player_fixture_set_up, video_player_test_set_video,
               video_player_fixture_tear_down);

    g_test_add("/video_player/test_set_size", VideoPlayerFixture, video_path->str,
               video_player_fixture_set_up, video_player_test_set_size,
               video_player_fixture_tear_down);

    g_test_add("/video_player/test_play", VideoPlayerFixture, video_path->str,
               video_player_fixture_set_up, video_player_test_play,
               video_player_fixture_tear_down);

    g_test_add("/video_player/test_pause", VideoPlayerFixture, video_path->str,
               video_player_fixture_set_up, video_player_test_pause,
               video_player_fixture_tear_down);
}

