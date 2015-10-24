#include "filebrowser.h"

#include <glib.h>
#include <string.h>

#include "filebrowser_p.h"

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

    self->current_node_ = NULL;

    G_OBJECT_CLASS(file_browser_parent_class)->dispose(browser);
}

static void file_browser_finalize(GObject *browser)
{
    FileBrowser *self = FILE_BROWSER(browser);

    g_node_destroy(self->root_node_);

    G_OBJECT_CLASS(file_browser_parent_class)->finalize(browser);
}

void file_browser_ref(FileBrowser *self)
{
    g_object_ref(self);
}

void file_browser_unref(FileBrowser *self)
{
    g_object_unref(self);
}

guint file_browser_set_root_path(FileBrowser *self, const gchar *path)
{
    if (self->root_node_)
    {
        g_node_destroy(self->root_node_);
        self->current_node_ = NULL;
    }

    g_return_val_if_fail(g_file_test(path, G_FILE_TEST_EXISTS | G_FILE_TEST_IS_DIR), 0);

    self->root_node_ = g_node_new((gpointer)path);
    self->current_node_ = self->root_node_;

    return file_browser_private_update_node_content(self->root_node_);
}

guint file_browser_change_directory(FileBrowser *self, const gchar *directory_name)
{
    guint current_node_child_count = 0;
    guint i;
    GNode *current_child_node = NULL;

    g_return_val_if_fail(self->root_node_ && self->current_node_, 0);

    current_node_child_count = g_node_n_children(self->current_node_);

    for (i = 0; i < current_node_child_count; ++i)
    {
        current_child_node = g_node_nth_child(self->current_node_, i);

        if (g_strcmp0(DIR_NAME(current_child_node), directory_name) == 0)
        {
            self->current_node_ = current_child_node;
            return file_browser_private_update_node_content(self->current_node_);
        }
    }

    return 0;
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

    return file_browser_private_build_path(self->current_node_, 0);
}

const gchar *file_browser_current_dir(FileBrowser *self)
{
    g_return_val_if_fail(self->root_node_ && self->current_node_, NULL);

    return DIR_NAME(self->current_node_);
}

guint file_browser_current_dir_file_count(FileBrowser *self)
{
    g_return_val_if_fail(self->root_node_ && self->current_node_, 0);

    return g_node_n_children(self->current_node_);
}

gchar **file_browser_current_dir_get_content(FileBrowser *self)
{
    gchar ** children;
    guint current_node_child_count;
    guint i;
    GNode *current_child_node = NULL;

    g_return_val_if_fail(self->root_node_ && self->current_node_, NULL);

    current_node_child_count = g_node_n_children(self->current_node_);

    children = (gchar **)g_malloc((current_node_child_count + 1) * sizeof(gchar *));
    children[current_node_child_count] = NULL;

    for (i = 0; i < current_node_child_count; ++i)
    {
        current_child_node = g_node_nth_child(self->current_node_, i);

        children[i] = g_strdup(DIR_NAME(current_child_node));
    }

    return children;
}

guint file_browser_private_update_node_content(GNode *node)
{
    GDir *dir = NULL;
    GError *error = NULL;
    GNode *entry = NULL;
    const gchar *entry_name = NULL;
    guint node_child_count = 0;
    guint i;
    gchar *path = file_browser_private_build_path(node, 0);

    dir = g_dir_open(path, 0, &error);
    g_return_val_if_fail((dir != NULL) && (error == NULL), 0);

    if ((node_child_count = g_node_n_children(node)) > 0)
    {
        for (i = 0; i < node_child_count; ++i)
            g_node_destroy(g_node_nth_child(node, i));
    }

    node_child_count = 0;

    while (TRUE)
    {
        entry_name = g_dir_read_name(dir);
        if (entry_name == NULL)
            break;

        entry = g_node_new((gpointer)g_strdup(entry_name));
        g_node_append(node, entry);
        node_child_count++;
    }

    g_dir_close(dir);
    g_free(path);

    return node_child_count;
}

gchar *file_browser_private_build_path(GNode *node, gsize size_hint)
{
    gsize position = size_hint <= 0 ? 2048 : size_hint;
    gchar path[position + 1];
    const gchar *entry_name = NULL;
    size_t entry_length = 0;
    gsize i;

    path[position] = '\0';

    while (TRUE)
    {
        entry_name = DIR_NAME(node);
        entry_length = strlen(entry_name);

        position -= entry_length;

        if (entry_name[0] == '/')
        {
            for (i = 0; i < entry_length; ++i)
            {
                path[i + position] = entry_name[i];
            }
        }
        else
        {
            path[position - 1] = '/';
            for (i = 0; i < entry_length; ++i)
            {
                path[i + position] = entry_name[i];
            }
            position--;
        }

        if (G_NODE_IS_ROOT(node))
            break;

        node = node->parent;
    }

    return g_strdup(&path[position]);
}
