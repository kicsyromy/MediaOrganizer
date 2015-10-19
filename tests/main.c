#include <glib.h>
#include <locale.h>

#include "test_videoplayer.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    g_test_init(&argc, &argv, NULL);
    g_type_init();

    video_player_tests_add();

    return g_test_run();
}
