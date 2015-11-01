#include "test_filebrowser.h"

#include "test_global.h"

#include "filebrowser_p.h"

void file_browser_fixture_set_up(FileBrowserFixture *fixture, gconstpointer data)
{
    UNUSED(data)

    fixture->browser_ = file_browser_new();
}

void file_browser_fixture_tear_down(FileBrowserFixture *fixture, gconstpointer data)
{
    UNUSED(data)

    file_browser_unref(fixture->browser_);
}

void file_browser_test_set_root_path(FileBrowserFixture *fixture, gconstpointer data)
{
    FileBrowser *browser = fixture->browser_;
    const gchar *root_path = (const gchar *)data;

    guint file_count = file_browser_set_root_path(fixture->browser_, root_path);

    BEGIN_TEST_CASE

    TEST_IS_NOT_NULL(browser->root_node_);
    TEST_IS_NULL(browser->root_node_->parent)
    TEST_IS_NOT_NULL(browser->current_node_);
    TEST_CMPPTR(browser->current_node_, ==, browser->root_node_);
    TEST_CMPINT(file_count, ==, 3);
    TEST_STREQ(root_path, file_browser_private_build_path(browser->current_node_, 0));

    END_TEST_CASE
}

void file_browser_test_change_directory(FileBrowserFixture *fixture, gconstpointer data)
{
    FileBrowser *browser = fixture->browser_;
    const gchar *root_path = (const gchar *)data;
    guint32 file_count = 0;
    GString *current_path = g_string_new(root_path);
    g_string_append(current_path, "/folder1");

    file_browser_set_root_path(fixture->browser_, root_path);
    file_count = file_browser_change_directory(browser, "folder1");

    BEGIN_TEST_CASE

    TEST_IS_NOT_NULL(browser->root_node_);
    TEST_IS_NULL(browser->root_node_->parent)
    TEST_IS_NOT_NULL(browser->current_node_);
    TEST_CMPPTR(browser->current_node_, !=, browser->root_node_);
    TEST_CMPINT(file_count, ==, 3);
    TEST_STREQ(current_path->str, file_browser_private_build_path(browser->current_node_, 0));

    END_TEST_CASE

    g_string_free(current_path, TRUE);
}

void file_browser_test_file_count(FileBrowserFixture *fixture, gconstpointer data)
{
    FileBrowser *browser = fixture->browser_;
    const gchar *root_path = (const gchar *)data;

    file_browser_set_root_path(fixture->browser_, root_path);

    BEGIN_TEST_CASE

    TEST_IS_NOT_NULL(browser->root_node_);
    TEST_IS_NULL(browser->root_node_->parent)
    TEST_IS_NOT_NULL(browser->current_node_);
    TEST_CMPPTR(browser->current_node_, ==, browser->root_node_);
    TEST_CMPINT(file_browser_current_dir_file_count(browser), ==, 3);

    END_TEST_CASE
}

void file_browser_test_get_content(FileBrowserFixture *fixture, gconstpointer data)
{
    FileBrowser *browser = fixture->browser_;
    const gchar *root_path = (const gchar *)data;

    guint file_count = file_browser_set_root_path(fixture->browser_, root_path);
    gchar **file_list = NULL;

    BEGIN_TEST_CASE

    TEST_IS_NOT_NULL(browser->root_node_);
    TEST_IS_NULL(browser->root_node_->parent)
    TEST_IS_NOT_NULL(browser->current_node_);
    TEST_CMPPTR(browser->current_node_, ==, browser->root_node_);
    TEST_CMPINT(file_count, ==, 3);
    TEST_IS_NOT_NULL((file_list = file_browser_current_dir_get_content(browser)));

    END_TEST_CASE

    g_strfreev(file_list);
}

void file_browser_tests_add()
{
    GString *root_path = g_string_new(TEST_DATA_PATH);
    g_string_append(root_path, "test_root_path");

    g_test_add("/file_browser/test_set_root_path", FileBrowserFixture,
               (gconstpointer)root_path->str,
               file_browser_fixture_set_up, file_browser_test_set_root_path,
               file_browser_fixture_tear_down);

    g_test_add("/file_browser/test_change_directory", FileBrowserFixture,
               (gconstpointer)root_path->str,
               file_browser_fixture_set_up, file_browser_test_change_directory,
               file_browser_fixture_tear_down);

    g_test_add("/file_browser/test_file_count", FileBrowserFixture,
               (gconstpointer)root_path->str,
               file_browser_fixture_set_up, file_browser_test_file_count,
               file_browser_fixture_tear_down);

    g_test_add("/file_browser/test_get_content", FileBrowserFixture,
               (gconstpointer)root_path->str,
               file_browser_fixture_set_up, file_browser_test_get_content,
               file_browser_fixture_tear_down);
}
