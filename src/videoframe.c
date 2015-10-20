#include "videoframe.h"
#include "videoframe_p.h"

#include <string.h>

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

void video_frame_ref(VideoFrame *self)
{
    g_object_ref(self);
}

void video_frame_unref(VideoFrame *self)
{
    g_object_unref(self);
}

FrameBufferType video_frame_get_buffer(VideoFrame *self, gsize *buffer_size)
{
    if (buffer_size)
        *buffer_size = self->buffer_size_;

    return self->buffer_;
}

VideoFrame *video_frame_copy(VideoFrame *self)
{
    VideoFrame *copy = NULL;

    void *buffer_copy = g_memdup(self->buffer_, self->buffer_size_);

    copy = VIDEO_FRAME(g_object_new(VIDEO_FRAME_TYPE, NULL));
    copy->buffer_ = buffer_copy;
    copy->buffer_size_ = self->buffer_size_;
    copy->width_ = self->width_;
    copy->height_ = self->height_;

    return copy;
}

gboolean video_frame_equals(VideoFrame *self, VideoFrame *other)
{
    gboolean are_equal = TRUE;

    are_equal = (self->width_ == other->width_) &&
                (self->height_ == other->height_) &&
                (self->buffer_size_ == other->buffer_size_);

    if (are_equal)
        are_equal = (memcmp(self->buffer_, other->buffer_, self->buffer_size_) == 0);

    return are_equal;
}

guint16 video_frame_get_width(VideoFrame *self)
{
    return self->width_;
}

guint16 video_frame_get_height(VideoFrame *self)
{
    return self->height_;
}
