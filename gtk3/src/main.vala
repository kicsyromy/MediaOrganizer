using GLib;

namespace MediaOrganizer
{
    Application global_app;

    public class Application: GLib.Application
    {
        public Application(string application_id)
        {
            Object(application_id: application_id,
                   flags:(ApplicationFlags.HANDLES_COMMAND_LINE));

            activate.connect(this.onActivated);
            startup.connect(this.onStartup);
            command_line.connect(this.onCommandLine);
        }

        private void onStartup()
        {

            stdout.printf("on_startup\n");
        }

        private int onCommandLine(ApplicationCommandLine command_line)
        {
            bool primary_instance = !command_line.get_is_remote ();

            if (primary_instance) {
                print ("Primary Instance Command Line !!!\n");
            } else {
                print ("Remote Command Line !!!\n");
            }

            return 0;
        }

        private void onActivated()
        {
            stdout.printf ("on_activated\n");
        }


        private static int main (string[] args)
        {
            global_app = new Application("ro.kicsyromy.MediaOrganizer");

            try {
                global_app.register (null);
            } catch (Error e) {
                print ("Application Error: %s\n", e.message);
                return -1;
            }

            if (!global_app.get_is_remote())
            {
                stdout.printf("No prior instance detected\n");
            }
            else
            {
                stdout.printf("A previous instance is already launched\n");
            }

            return global_app.run(args);
        }
    }
}
