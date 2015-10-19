#include "test_videoplayer.h"

#include "videoplayer_p.h"

void video_player_fixture_set_up(VideoPlayerFixture *fixture, gconstpointer file_path)
{
    fixture->player_ = video_player_new();
    video_player_set_source(fixture->player_, (const gchar *)file_path);
}

void video_player_fixture_tear_down(VideoPlayerFixture *fixture)
{
    g_object_unref(fixture->player_);
}

void video_player_test_init(VideoPlayerFixture *fixture, gconstpointer file_path)
{
    VideoPlayer *player = fixture->player_;

    g_assert_cmpint(player->callbacks_.callback_data_, ==, 0);
    g_assert_cmpint(player->callbacks_.render_cb_, == , 0);
    g_assert_cmpint(player->callbacks_.pos_changed_cb_, ==, 0);
    g_assert_cmpint(player->frame_.last_frame_, ==, 0);
    g_assert_cmpint(player->video_data_.vlc_instance_, !=, 0);
    g_assert_cmpint(player->video_data_.vlc_media_player_, ==, 0);
    g_assert_cmpint(player->video_data_.vlc_event_mgr_, ==, 0);
    g_assert_cmpint(player->video_data_.width, ==, 0);
    g_assert_cmpint(player->video_data_.height, ==, 0);
}

void video_player_tests_add()
{
    g_test_add("/video_player/test1", VideoPlayerFixture, "file_path",
               video_player_fixture_set_up, video_player_test_init,
               video_player_fixture_tear_down);
}
