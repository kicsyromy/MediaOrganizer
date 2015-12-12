namespace File {
    [CCode (cheader_filename = "libmo.h")]
    public class Browser : GLib.Object {
        [CCode (cname = "file_browser_new", has_construct_function = false, type = "FileBrowser*")]
        public Browser ();
        [CCode (cname = "file_browser_change_directory")]
        public uint change_directory(string directory_name);
        [CCode (cname = "file_browser_current_dir")]
        public unowned string current_dir();
        [CCode (cname = "file_browser_current_dir_file_count")]
        public uint current_dir_file_count();
        [CCode (cname = "file_browser_current_dir_get_content")]
        public unowned string [] current_dir_get_content();
        [CCode (cname = "file_browser_current_path")]
        public unowned string current_path();
        [CCode (cname = "file_browser_set_root_path")]
        public uint set_root_path(string path);
        [CCode (cname = "file_browser_to_parent")]
        public void to_parent();
        [CCode (cname = "file_browser_to_root")]
        public void to_root();
    }
}

namespace Video {
    [CCode (cheader_filename = "libmo.h")]
    public class Frame : GLib.Object {
        [CCode (has_construct_function = false)]
        protected Frame();
        [CCode (cname = "video_frame_copy")]
        public Frame.copy(Frame frame);
        [CCode (cname = "video_frame_equals")]
        public bool equals(Frame other);
        [CCode (cname = "video_frame_get_buffer")]
        public unowned uint8[] get_buffer();
        [CCode (cname = "video_frame_get_height")]
        public uint16 get_height();
        [CCode (cname = "video_frame_get_width")]
        public uint16 get_width();
    }
    [CCode (cheader_filename = "libmo.h")]
    public class Player : GLib.Object {
        [CCode (cname = "video_player_new", has_construct_function = false, type = "VideoPlayer*")]
        public Player();
        [CCode (cname = "video_player_generate_thumbnail")]
        public static Frame generate_thumbnail(string video_path, float position, uint16 width, uint16 height);
        [CCode (cname = "video_player_get_current_time")]
        public int64 get_current_time();
        [CCode (cname = "video_player_get_duration")]
        public int64 get_duration();
        [CCode (cname = "video_player_get_width")]
        public uint16 get_width();
        [CCode (cname = "video_player_get_height")]
        public uint16 get_height();
        [CCode (cname = "video_player_pause")]
        public void pause();
        [CCode (cname = "video_player_play")]
        public void play();
        [CCode (cname = "video_player_set_muted")]
        public void set_muted(bool muted);
        [CCode (cname = "video_player_set_position")]
        public void set_position(float position);
        [CCode (cname = "video_player_set_position_changed_callback")]
        public void set_position_changed_callback(PositionChangedCallback cb);
        [CCode (cname = "video_player_set_render_callback")]
        public void set_render_callback(RenderCallback cb);
        [CCode (cname = "video_player_set_size")]
        public void set_size(uint16 width, uint16 height);
        [CCode (cname = "video_player_set_source")]
        public void set_source(string path);
        [CCode (cname = "video_player_set_time")]
        public void set_time(int64 position);
        [CCode (cname = "video_player_set_volume")]
        public void set_volume(uchar volume);
        [CCode (cname = "video_player_stop")]
        public void stop();
    }
    [CCode (cheader_filename = "libmo.h")]
    public delegate void PositionChangedCallback (float new_position);
    [CCode (cheader_filename = "libmo.h")]
    public delegate void RenderCallback (Frame frame);
}
