#include "filebrowser.h"

struct _FileBrowser
{
    GObject parent;
};

struct _FileBrowserClass
{
    GObjectClass parent;
};

G_DEFINE_TYPE(FileBrowser, file_browser, G_TYPE_OBJECT)
static void file_browser_init(FileBrowser *self);
static void file_browser_class_init(FileBrowserClass *klass);
//static void file_browser_dispose(GObject *browser);

FileBrowser *file_browser_new()
{
    return FILE_BROWSER(g_object_new(FILE_BROWSER_TYPE, NULL));
}

static void file_browser_init(FileBrowser *self)
{
    UNUSED(self)
}

static void file_browser_class_init(FileBrowserClass *klass)
{
    UNUSED(klass)
}

void file_browser_set_root_path(FileBrowser *self, const gchar *path)
{
    UNUSED(self)
    UNUSED(path)
}

void file_browser_change_directory(FileBrowser *self, const gchar *directory_name)
{
    UNUSED(self)
    UNUSED(directory_name)
}

void file_browser_to_parent(FileBrowser *self)
{
    UNUSED(self)
}

void file_browser_to_root(FileBrowser *self)
{
    UNUSED(self)
}

const gchar *file_browser_current_path(FileBrowser *self)
{
    UNUSED(self)

    return NULL;
}

const gchar *file_browser_current_dir(FileBrowser *self)
{
    UNUSED(self)

    return NULL;
}

guint64 file_browser_current_dir_file_count(FileBrowser *self)
{
    UNUSED(self)

    return 0;
}

const gchar **file_browser_current_dir_get_content(FileBrowser *self)
{
    UNUSED(self)

    return NULL;
}
