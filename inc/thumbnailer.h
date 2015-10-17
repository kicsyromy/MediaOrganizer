#ifndef THUMBNAILER_H
#define THUMBNAILER_H

#include <mo_global.h>

C_STYLE_BEGIN

#include <glib-object.h>

#define THUMBNAILER_TYPE thumbnailer_get_type()
#define THUMBNAILER(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), THUMBNAILER_TYPE, Thumbnailer))

typedef struct _Thumbnailer         Thumbnailer;
typedef struct _ThumbnailerClass    ThumbnailerClass;

typedef struct _VideoFrame          VideoFrame;

MO_API  GType thumbnailer_get_type();

MO_API  Thumbnailer *thumbnailer_new();
MO_API  void thumbnailer_set_source(Thumbnailer *thumbnailer, const gchar *path);
MO_API  void thumbnailer_set_size(Thumbnailer *thumbnailer, const guint16 width, const guint16 height);
MO_API  void thumbnailer_set_position(Thumbnailer *thumbnailer, const gfloat position);
MO_API  VideoFrame *thumbnailer_generate_thumbnail(Thumbnailer *thumbnailer);

C_STYLE_END

#endif // THUMBNAILER_H
