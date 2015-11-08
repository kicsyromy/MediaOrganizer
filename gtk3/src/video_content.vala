using Gtk;
using Cairo;
using Video;

namespace MediaOrganizer
{
    public class VideoContent : Gtk.Box
    {
        public VideoContent(string videoPath)
        {
            Object(orientation: Gtk.Orientation.VERTICAL,
                   spacing: 0);

            player_ = new Video.Player();
            player_.setSource(videoPath);
            player_.setRenderCallback(onNewFrameReady);

            surface_ = new Gtk.DrawingArea();
            surface_.draw.connect(onDraw);

            pack_start(surface_);
        }

        public void setSize(uint16 width, uint16 height)
        {
        }

        public void setSource(string videoPath)
        {
            player_.setSource(videoPath);
        }

        public void play()
        {
            player_.play();
        }

        public void stop()
        {
            player_.stop();
        }

        private bool onDraw(Widget da, Context ctx)
        {
            ctx.set_source_surface(frame_, 0, 0);
            ctx.paint();

            return true;
        }

        private void onNewFrameReady(Video.Frame frame)
        {
            var frameBuffer = frame.getBuffer();
            Format format = Cairo.Format.RGB24;
            frame_ = new ImageSurface.for_data(frameBuffer,
                format,
                frame.getWidth(),
                frame.getHeight(),
                format.stride_for_width(frame.getWidth()));

            surface_.queue_draw();
        }

        private Gtk.DrawingArea surface_;
        private Cairo.Surface frame_;
        private Video.Player player_;
    }
}
