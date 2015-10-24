#include <glib.h>
#include <locale.h>

#include "mo_config.h"

#include "test_videoplayer.h"
#include "test_filebrowser.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);
    g_type_init();

    g_print("Starting unit tests for libmo version %d.%d.%d\n",
            MediaOrganizer_VERSION_MAJOR,
            MediaOrganizer_VERSION_MINOR,
            MediaOrganizer_VERSION_PATCH);

#ifdef TEST_VIDEO_PLAYER
    video_player_tests_add();
#endif
#ifdef TEST_FILE_BROWSER
    file_browser_tests_add();
#endif

    return g_test_run();
}
