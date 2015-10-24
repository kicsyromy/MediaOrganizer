#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <mo_global.h>

C_STYLE_BEGIN

#include <glib-object.h>

#define FILE_BROWSER_TYPE file_browser_get_type()
#define FILE_BROWSER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), FILE_BROWSER_TYPE, FileBrowser))

typedef struct _FileBrowser         FileBrowser;
typedef struct _FileBrowserClass    FileBrowserClass;

MO_API  GType file_browser_get_type();

MO_API  void file_browser_ref(FileBrowser *browser);
MO_API  void file_browser_unref(FileBrowser *browser);

MO_API  FileBrowser *file_browser_new();
MO_API  guint file_browser_set_root_path(FileBrowser *browser, const gchar *path);
MO_API  guint file_browser_change_directory(FileBrowser *browser, const gchar *directory_name);
MO_API  void file_browser_to_parent(FileBrowser *browser);
MO_API  void file_browser_to_root(FileBrowser *browser);
MO_API  const gchar *file_browser_current_path(FileBrowser *browser);
MO_API  const gchar *file_browser_current_dir(FileBrowser *browser);
MO_API  guint file_browser_current_dir_file_count(FileBrowser *browser);
MO_API  gchar **file_browser_current_dir_get_content(FileBrowser *browser);

C_STYLE_END

#endif // FILEBROWSER_H
