#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#include <mo_global.h>

C_STYLE_BEGIN

#include <glib-object.h>

#define VIDEO_FRAME_TYPE video_frame_get_type()
#define VIDEO_FRAME(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), VIDEO_FRAME_TYPE, VideoFrame))

typedef struct _VideoFrame         VideoFrame;
typedef struct _VideoFrameClass    VideoFrameClass;

typedef guint8 * FrameBufferType;

MO_API  GType video_frame_get_type();

MO_API  FrameBufferType video_frame_get_buffer(VideoFrame *frame, gsize *buffer_size);
MO_API  VideoFrame *video_frame_copy(VideoFrame *frame);
MO_API  guint16 video_frame_get_width(VideoFrame *frame);
MO_API  guint16 video_frame_get_height(VideoFrame *frame);

C_STYLE_END

#endif // VIDEOFRAME_H
