#ifndef FILEBROWSER_P_H
#define FILEBROWSER_P_H

#include <mo_global.h>

C_STYLE_BEGIN

#include "filebrowser.h"

#define DIR_NAME(node) (const gchar *)node->data

struct _FileBrowser
{
    GObject parent;

    GNode *root_node_;
    GNode *current_node_;
};

struct _FileBrowserClass
{
    GObjectClass parent;
};

guint file_browser_private_update_node_content(GNode *node);
gchar *file_browser_private_build_path(GNode *node, gsize size_hint);

C_STYLE_END

#endif // FILEBROWSER_P_H
