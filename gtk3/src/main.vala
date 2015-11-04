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

            activate.connect(onActivated);
        }

        private void onActivated()
        {
            if (!get_is_remote())
            {
                mainWindow_ = new MainWindow("Hello Vala MainWindow");
                add_window(mainWindow_);

                mainWindow_.show_all();
            }
        }

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
            print("Application Error: %s\n", e.message);
            return -1;
        }

        return application.run(args);
    }
}
