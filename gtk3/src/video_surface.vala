using Gtk;
using Cairo;

namespace MediaOrganizer
{
    public class VideoSurface: Gtk.Box
    {
        public VideoSurface()
        {
            Object(orientation: Gtk.Orientation.VERTICAL,
                   spacing: 0);

            surface_ = new Gtk.DrawingArea();
            surface_.set_size_request(800, 480);
            surface_.draw.connect(onDraw);

            var frame = VideoPlayer.generate_thumbnail("/media/Shared/Downloads/Comedy.Central.Roast.of.James.Franco.UNCENSORED.720p.WEB-DL.x264.AAC/The.Comedy.Central.Roast.of.James.Franco.2013.UNCENSORED.720p.WEB-DL.x264.AAC.mp4",
                                           0.8f,
                                           800,
                                           480);

            var frameBuffer = frame.getBuffer();
            Format format = Cairo.Format.RGB24;
            frame_ = new ImageSurface.for_data(frameBuffer, format, 800, 480, format.stride_for_width(800));
            pack_start(surface_);
        }

        private bool onDraw(Widget da, Context ctx)
        {
            ctx.set_source_surface(frame_, 0, 0);
            ctx.paint();

            return true;
        }

        private Gtk.DrawingArea surface_;
        private Cairo.Surface frame_;
    }
}
