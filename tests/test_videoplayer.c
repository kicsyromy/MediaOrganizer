#include "test_videoplayer.h"

void video_player_fixture_set_up_empty(VideoPlayerFixture *fixture)
{
    UNUSED(fixture)
}

void video_player_fixture_set_up_with_video(VideoPlayerFixture *fixture, const gchar *file_path)
{
    UNUSED(fixture)
    UNUSED(file_path)
}

void video_player_fixture_set_up_with_video_and_size(VideoPlayerFixture *fixture,
                                                     const gchar *file_path,
                                                     const guint16 width,
                                                     const guint16 height)
{
    UNUSED(fixture)
    UNUSED(file_path)
    UNUSED(width)
    UNUSED(height)
}

void video_player_fixture_tear_down(VideoPlayerFixture *fixture)
{
    UNUSED(fixture)
}
