using GLib;
using Gtk;

namespace MediaOrganizer
{
    public class MainWindow: Gtk.Window
    {
        /* public constructor(s)/destructor*/
        public MainWindow(string title)
        {
            this.border_width = 10;
            this.window_position = WindowPosition.CENTER;
            this.set_default_size(800, 480);

            header_ = new Gtk.HeaderBar();
            header_.set_title(title);
            header_.set_show_close_button(true);
            this.set_titlebar(header_);

            video_ = new VideoContent("/media/Shared/Downloads/Terminator.Genisys.2015.1080p.HC.HDRip.X264.AC3-EVO/sample.mkv");
            video_.play();

            this.size_allocate.connect(onSizeChanged);

            add(video_);
        }

        void onSizeChanged(Gtk.Allocation size)
        {
            video_.setSize((uint16)this.get_allocated_width(), (uint16)this.get_allocated_height());
        }

        /* private variables */
        private Gtk.HeaderBar header_;
        private VideoContent video_;
    }
}
