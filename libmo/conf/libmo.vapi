[CCode (cheader_filename = "libmo.h")]
public class FileBrowser : GLib.Object {
    [CCode (cname = "file_browser_new", has_construct_function = false, type = "FileBrowser*")]
    public FileBrowser ();
    [CCode (cname = "file_browser_change_directory")]
    public static uint change_directory (FileBrowser browser, string directory_name);
    [CCode (cname = "file_browser_current_dir")]
    public static unowned string current_dir (FileBrowser browser);
    [CCode (cname = "file_browser_current_dir_file_count")]
    public static uint current_dir_file_count (FileBrowser browser);
    [CCode (cname = "file_browser_current_dir_get_content")]
    public static unowned string current_dir_get_content (FileBrowser browser);
    [CCode (cname = "file_browser_current_path")]
    public static unowned string current_path (FileBrowser browser);
    [CCode (cname = "file_browser_ref")]
    public static void @ref (FileBrowser browser);
    [CCode (cname = "file_browser_set_root_path")]
    public static uint set_root_path (FileBrowser browser, string path);
    [CCode (cname = "file_browser_to_parent")]
    public static void to_parent (FileBrowser browser);
    [CCode (cname = "file_browser_to_root")]
    public static void to_root (FileBrowser browser);
    [CCode (cname = "file_browser_unref")]
    public static void unref (FileBrowser browser);
}
[CCode (cheader_filename = "libmo.h")]
[Compact]
public class FileBrowserClass {
}
namespace Video
{
    [CCode (cheader_filename = "libmo.h")]
    public class Frame : GLib.Object {
        [CCode (has_construct_function = false)]
        protected Frame();
        [CCode (cname = "video_frame_copy")]
        public Frame.copy(Frame frame);
        [CCode (cname = "video_frame_equals")]
        public bool equals(Frame other);
        [CCode (cname = "video_frame_get_buffer")]
        public unowned uint8[] getBuffer();
        [CCode (cname = "video_frame_get_height")]
        public uint16 getHeight();
        [CCode (cname = "video_frame_get_width")]
        public uint16 getWidth();
    }
    [CCode (cheader_filename = "libmo.h")]
    public class Player : GLib.Object {
        [CCode (cname = "video_player_new", has_construct_function = false, type = "VideoPlayer*")]
        public Player();
        [CCode (cname = "video_player_generate_thumbnail")]
        public static Frame generateThumbnail(string video_path, float position, uint16 width, uint16 height);
        [CCode (cname = "video_player_get_current_time")]
        public int64 getCurrentTime();
        [CCode (cname = "video_player_get_duration")]
        public int64 getDuration();
        [CCode (cname = "video_player_get_width")]
        public uint16 getWidth();
        [CCode (cname = "video_player_get_height")]
        public uint16 getHeight();
        [CCode (cname = "video_player_pause")]
        public void pause();
        [CCode (cname = "video_player_play")]
        public void play();
        [CCode (cname = "video_player_set_muted")]
        public void setMuted(bool muted);
        [CCode (cname = "video_player_set_position")]
        public void setPosition(float position);
        [CCode (cname = "video_player_set_position_changed_callback")]
        public void setPositionChangedCallback(PositionChangedCallback cb);
        [CCode (cname = "video_player_set_render_callback")]
        public void setRenderCallback(RenderCallback cb);
        [CCode (cname = "video_player_set_size")]
        public void setSize(uint16 width, uint16 height);
        [CCode (cname = "video_player_set_source")]
        public void setSource(string path);
        [CCode (cname = "video_player_set_time")]
        public void setTime(int64 position);
        [CCode (cname = "video_player_set_volume")]
        public void setVolume(uchar volume);
        [CCode (cname = "video_player_stop")]
        public void stop();
    }
    [CCode (cheader_filename = "libmo.h")]
    public delegate void PositionChangedCallback (float new_position);
    [CCode (cheader_filename = "libmo.h")]
    public delegate void RenderCallback (Frame frame);
}
