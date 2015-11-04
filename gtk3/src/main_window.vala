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

            surface_ = new VideoSurface();

            add(surface_);
        }

        /* private variables */
        private Gtk.HeaderBar header_;
        private VideoSurface surface_;
    }
}
