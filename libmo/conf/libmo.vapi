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
[CCode (cheader_filename = "libmo.h")]
public class VideoFrame : GLib.Object {
    [CCode (has_construct_function = false)]
    protected VideoFrame ();
    [CCode (cname = "video_frame_copy")]
    public VideoFrame copy (VideoFrame frame);
    [CCode (cname = "video_frame_equals")]
    public bool equals (VideoFrame other);
    [CCode (cname = "video_frame_get_buffer")]
    public uint8[] getBuffer ();
    [CCode (cname = "video_frame_get_height")]
    public uint16 getHeight ();
    [CCode (cname = "video_frame_get_width")]
    public uint16 getWidth ();
}
[CCode (cheader_filename = "libmo.h")]
public class VideoPlayer : GLib.Object {
    [CCode (cname = "video_player_new", has_construct_function = false, type = "VideoPlayer*")]
    public VideoPlayer ();
    [CCode (cname = "video_player_generate_thumbnail")]
    public static unowned VideoFrame generate_thumbnail (string video_path, float position, uint16 width, uint16 height);
    [CCode (cname = "video_player_get_current_time")]
    public static int64 get_current_time (VideoPlayer player);
    [CCode (cname = "video_player_get_duration")]
    public static int64 get_duration (VideoPlayer player);
    [CCode (cname = "video_player_pause")]
    public static void pause (VideoPlayer player);
    [CCode (cname = "video_player_play")]
    public static void play (VideoPlayer player);
    [CCode (cname = "video_player_ref")]
    public static void @ref (VideoPlayer player);
    [CCode (cname = "video_player_set_callback_data")]
    public static void set_callback_data (VideoPlayer player, void* callback_data);
    [CCode (cname = "video_player_set_muted")]
    public static void set_muted (VideoPlayer player, bool muted);
    [CCode (cname = "video_player_set_position")]
    public static void set_position (VideoPlayer player, float position);
    [CCode (cname = "video_player_set_position_changed_callback")]
    public static void set_position_changed_callback (VideoPlayer player, PositionChangedCallback cb);
    [CCode (cname = "video_player_set_render_callback")]
    public static void set_render_callback (VideoPlayer player, RenderCallback cb);
    [CCode (cname = "video_player_set_size")]
    public static void set_size (VideoPlayer player, uint16 width, uint16 height);
    [CCode (cname = "video_player_set_source")]
    public static void set_source (VideoPlayer player, string path);
    [CCode (cname = "video_player_set_time")]
    public static void set_time (VideoPlayer player, int64 position);
    [CCode (cname = "video_player_set_volume")]
    public static void set_volume (VideoPlayer player, uchar volume);
    [CCode (cname = "video_player_stop")]
    public static void stop (VideoPlayer player);
    [CCode (cname = "video_player_unref")]
    public static void unref (VideoPlayer player);
}
[CCode (cheader_filename = "libmo.h")]
[Compact]
public class VideoPlayerClass {
}
[CCode (cheader_filename = "libmo.h")]
public delegate void PositionChangedCallback (float new_position);
[CCode (cheader_filename = "libmo.h")]
public delegate void RenderCallback (VideoFrame frame);
