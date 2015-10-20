#include "filebrowser.h"

#include <glib.h>

#define DIR_NAME(node) (const gchar *)node->data

struct _FileBrowser
{
    GObject parent;

    GNode *root_node_;
    GNode *current_node_;
    GString *current_path_;
};

struct _FileBrowserClass
{
    GObjectClass parent;
};

G_DEFINE_TYPE(FileBrowser, file_browser, G_TYPE_OBJECT)
static void file_browser_init(FileBrowser *self);
static void file_browser_class_init(FileBrowserClass *klass);
static void file_browser_dispose(GObject *browser);
static void file_browser_finalize(GObject *browser);

FileBrowser *file_browser_new()
{
    FileBrowser *self = FILE_BROWSER(g_object_new(FILE_BROWSER_TYPE, NULL));
    self->root_node_ = NULL;
    self->current_node_ = NULL;

    return self;
}

static void file_browser_init(FileBrowser *self)
{
    UNUSED(self)
}

static void file_browser_class_init(FileBrowserClass *klass)
{
    G_OBJECT_CLASS(klass)->dispose = file_browser_dispose;
    G_OBJECT_CLASS(klass)->finalize = file_browser_finalize;
}

static void file_browser_dispose(GObject *browser)
{
    FileBrowser *self = FILE_BROWSER(browser);

    g_clear_object(&self->root_node_);

    G_OBJECT_CLASS(file_browser_parent_class)->dispose(browser);
}

static void file_browser_finalize(GObject *browser)
{
    FileBrowser *self = FILE_BROWSER(browser);

    g_node_destroy(self->root_node_);

    G_OBJECT_CLASS(file_browser_parent_class)->finalize(browser);
}

void file_browser_set_root_path(FileBrowser *self, const gchar *path)
{
    if (self->root_node_)
    {
        g_node_destroy(self->root_node_);
        self->current_node_ = NULL;
    }

    self->root_node_ = g_node_new((void *)path);
    self->current_node_ = self->root_node_;
}

void file_browser_change_directory(FileBrowser *self, const gchar *directory_name)
{
    guint current_node_child_cout = 0;
    guint i;
    GNode *current_child_node = NULL;

    g_return_if_fail(self->root_node_ && self->current_node_);

    current_node_child_cout = g_node_n_children(self->current_node_);

    for (i = 0; i < current_node_child_cout; ++i)
    {
        current_child_node = g_node_nth_child(self->current_node_, i);

        if (g_strcmp0(DIR_NAME(current_child_node), directory_name) == 0)
        {
            self->current_node_ = current_child_node;
            break;
        }
    }
}

void file_browser_to_parent(FileBrowser *self)
{
    g_return_if_fail(self->root_node_ && self->current_node_);

    self->current_node_ = self->current_node_->parent;
}

void file_browser_to_root(FileBrowser *self)
{
    self->current_node_ = self->root_node_;
}

const gchar *file_browser_current_path(FileBrowser *self)
{
    g_return_val_if_fail(self->root_node_ && self->current_node_, NULL);

    return self->current_path_->str;
}

const gchar *file_browser_current_dir(FileBrowser *self)
{
    g_return_val_if_fail(self->root_node_ && self->current_node_, NULL);

    return DIR_NAME(self->current_node_);
}

guint64 file_browser_current_dir_file_count(FileBrowser *self)
{
    g_return_val_if_fail(self->root_node_ && self->current_node_, 0);

    return g_node_n_children(self->current_node_);
}

gchar **file_browser_current_dir_get_content(FileBrowser *self)
{
    guint current_node_child_count;
    guint i;
    GNode *current_child_node = NULL;

    g_return_val_if_fail(self->root_node_ && self->current_node_, NULL);

    current_node_child_count = g_node_n_children(self->current_node_);

    gchar ** children = (gchar **)g_malloc(current_node_child_count * sizeof(gchar *));

    for (i = 0; i < current_node_child_count; ++i)
    {
        current_child_node = g_node_nth_child(self->current_node_, i);

        children[i] = g_strdup(DIR_NAME(current_child_node));
    }

    return children;
}
