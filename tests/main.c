#include <glib.h>
#include <locale.h>

#include "test_videoplayer.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);

//    g_test_bug_base("http://issue.tracker");

//    g_test_add("/video_player/test1", VideoPlayerFixture, "some_data",
//               video_player_fixture_set_up_empty, video_player_test1,
//               video_player_fixture_tear_down);

    return g_test_run();
}
