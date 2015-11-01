using GLib;

namespace MediaOrganizer
{
    Application application;

    public class Application: Gtk.Application
    {
        /* public constructor(s)/destructor*/
        public Application(string application_id)
        {
            Object(application_id: application_id);

            activate.connect(this.onActivated);
            startup.connect(this.onStartup);
        }

        /* public methods */
        /* TBD */

        /* private methods */
        private void onStartup()
        {
            stdout.printf("on_startup\n");
        }

        private void onActivated()
        {
            if (!application.get_is_remote())
            {
                mainWindow_ = new MainWindow("Hello Vala MainWindow");
                this.add_window(mainWindow_);
            }
        }

        private void showMainWindow()
        {
            mainWindow_.show_all();
        }

        /* private variables */
        private MainWindow mainWindow_;
    }

    int main(string[] args)
    {
        application = new Application("ro.kicsyromy.MediaOrganizer");

        try
        {
            application.register(null);
        }
        catch(Error e)
        {
            print ("Application Error: %s\n", e.message);
            return -1;
        }

        if (!application.get_is_remote())
            application.showMainWindow();
        else
            stdout.printf("MediaOrganizer is already running\n");

        return application.run(args);
    }
}
