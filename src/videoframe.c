#include "videoframe.h"

C_STYLE_BEGIN

#include "videoframe_p.h"

G_DEFINE_TYPE(VideoFrame, video_frame, G_TYPE_OBJECT)
static void video_frame_init(VideoFrame *self);
static void video_frame_class_init(VideoFrameClass *klass);
static void video_frame_finalize(GObject *video_frame);

static void video_frame_init(VideoFrame *self)
{
    self->buffer_ = NULL;
    self->buffer_size_ = 0;
    self->width_ = 0;
    self->height_ = 0;
}

static void video_frame_class_init(VideoFrameClass *klass)
{
    G_OBJECT_CLASS(klass)->finalize = video_frame_finalize;
}

static void video_frame_finalize(GObject *video_frame)
{
    VideoFrame *self = VIDEO_FRAME(video_frame);

    g_free(self->buffer_);
    self->buffer_ = NULL;

    G_OBJECT_CLASS(video_frame_parent_class)->dispose(video_frame);
}

FrameBufferType video_frame_get_buffer(VideoFrame *self, gsize *buffer_size)
{
    *buffer_size = self->buffer_size_;

    return self->buffer_;
}

guint16 video_frame_get_width(VideoFrame *self)
{
    return self->width_;
}

guint16 video_frame_get_height(VideoFrame *self)
{
    return self->height_;
}

C_STYLE_END
