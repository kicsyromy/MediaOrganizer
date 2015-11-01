#ifndef VIDEOFRAME_DEF_H
#define VIDEOFRAME_DEF_H

#include <mo_global.h>

C_STYLE_BEGIN

#include "videoplayer.h"
#include "videoframe.h"

struct _VideoFrame
{
    GObject parent;

    FrameBufferType buffer_;
    gsize buffer_size_;
    guint16 width_;
    guint16 height_;
};

struct _VideoFrameClass
{
    GObjectClass parent;
};

C_STYLE_END

#endif // VIDEOFRAME_DEF_H
