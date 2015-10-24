#ifndef TEST_FILEBROWSER_H
#define TEST_FILEBROWSER_H

#include <filebrowser.h>

C_STYLE_BEGIN

typedef struct
{
    FileBrowser *browser_;
}
FileBrowserFixture;

void file_browser_fixture_set_up(FileBrowserFixture *fixture, gconstpointer data);
void file_browser_fixture_tear_down(FileBrowserFixture*fixture, gconstpointer data);
void file_browser_test_set_root_path(FileBrowserFixture *fixture, gconstpointer data);
void file_browser_test_change_directory(FileBrowserFixture *fixture, gconstpointer data);
void file_browser_test_file_count(FileBrowserFixture *fixture, gconstpointer data);
void file_browser_tests_add();

C_STYLE_END

#endif // TEST_FILEBROWSER_H
