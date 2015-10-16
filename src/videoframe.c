#include "videoframe.h"

C_STYLE_BEGIN

#include "videoframe.h"
#include "videoframe_def.h"

G_DEFINE_TYPE(VideoFrame, video_frame, G_TYPE_OBJECT)
static void video_frame_init(VideoFrame *self);
static void video_frame_class_init(VideoFrameClass *klass);
static void video_frame_finalize(GObject *video_frame);

static void video_frame_init(VideoFrame *self)
{
    UNUSED(self)
}

static void video_frame_class_init(VideoFrameClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = video_frame_finalize;
}

static void video_frame_finalize(GObject *video_frame)
{
    UNUSED(video_frame)
}

FrameBufferType video_frame_get_buffer(VideoFrame *frame, gsize *buffer_size)
{
    UNUSED(frame)
    UNUSED(buffer_size)
}

guint16 video_frame_get_width(VideoFrame *frame)
{
    UNUSED(frame)
}

guint16 video_frame_get_height(VideoFrame *frame)
{
    UNUSED(frame)
}

C_STYLE_END
