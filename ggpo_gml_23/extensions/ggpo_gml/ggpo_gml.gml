#define ggpo_preinit
//show_message("?");
global.__ggpo_script_execute = method(undefined, script_execute);
global.__ggpo_script_execute_ptr = ptr(global.__ggpo_script_execute);
global.__ggpo_fixed_buffer = buffer_create(1024, buffer_fixed, 1);
switch (ggpo_preinit_1(global.__ggpo_script_execute_ptr)) {
    case 1:
        ggpo_preinit_2(global.__ggpo_fixed_buffer);
        show_debug_message("GGPO native extension loaded!");
        break;
    default:
        show_debug_message("GGPO native extension is unavailable.");
        break;
}
//#global ggpo_game_state_base_size
ggpo_game_state_base_size = 1024;
global.__ggpo_game_state_buffers = ds_map_create(); /// @is {ds_map<int, buffer>} (int64(ptr()), state_buf)

//#global ggpo_on_game_state_save
ggpo_on_game_state_save = asset_get_index("ggpo_default_game_state_save");
//#global ggpo_on_game_state_load
ggpo_on_game_state_load = asset_get_index("ggpo_default_game_state_load");
//#global ggpo_on_game_state_dump
ggpo_on_game_state_dump = asset_get_index("ggpo_default_game_state_dump");
//#global ggpo_on_game_begin
ggpo_on_game_begin = asset_get_index("ggpo_default_game_begin");
//#global ggpo_on_advance_frame
ggpo_on_advance_frame = asset_get_index("ggpo_default_advance_frame");
//#global ggpo_on_event
ggpo_on_event = asset_get_index("ggpo_default_event");

#define ggpo_default_game_state_save
show_error("Please implement ggpo_on_game_state_save (buffer, frame)", 1);

#define ggpo_default_game_state_load
show_error("Please implement ggpo_on_game_state_load (buffer, size)", 1);

#define ggpo_default_game_state_dump
show_error("Please implement ggpo_on_game_state_dump", 1);

#define ggpo_default_advance_frame
show_error("Please implement ggpo_on_advance_frame", 1);

#define ggpo_default_game_begin
exit; // if this script is completely empty, the game will hard crash

#define ggpo_default_event
var _ev = argument0;
show_debug_message(ggpo_eventcode_get_name(_ev.code) + ": " + string(_ev));
if (_ev.code == ggpo_eventcode_timesync) {
    ggpo_sleep(_ev.frames_ahead * game_get_speed(gamespeed_microseconds) / 1000)
}

#define ggpo_do_game_state_save_2
// (frame)
var _buf = buffer_create(ggpo_game_state_base_size, buffer_grow, 1);
ggpo_on_game_state_save(_buf, argument0);
global.__ggpo_game_state_buffers[?int64(buffer_get_address(_buf))] = _buf;
ggpo_do_game_state_save_3(_buf);

#define ggpo_do_game_state_load_2
// (addr, len)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) return false;
buffer_seek(_buf, buffer_seek_start, 0);
ggpo_on_game_state_load(_buf, argument1);
return true;

#define ggpo_do_game_state_dump_2
// (addr, len)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) return false;
var _fb = global.__ggpo_fixed_buffer;
buffer_seek(_fb, buffer_seek_start, 0);
var _name = buffer_read(_fb, buffer_string);
var _result = ggpo_on_game_state_dump(_buf, _name, argument1);
return _result == undefined || _result;

#define ggpo_do_game_state_free_2
// (addr)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) return false;
buffer_delete(_buf);
ds_map_delete(global.__ggpo_game_state_buffers, argument0);
return true;

#define ggpo_do_game_begin_2
// ()
ggpo_on_game_begin();

#define ggpo_do_advance_frame_2
// ()
ggpo_on_advance_frame()

#define ggpo_do_event_2
// ()
var _fb = global.__ggpo_fixed_buffer;
buffer_seek(_fb, buffer_seek_start, 0);
var _code = buffer_read(_fb, buffer_s32);
var _ev = { code: _code };
switch (_code) {
    case ggpo_eventcode_connected_to_peer:
        _ev.player = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_synchronizing_with_peer:
        _ev.player = buffer_read(_fb, buffer_s32);
        _ev.count = buffer_read(_fb, buffer_s32);
        _ev.total = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_synchronized_with_peer:
        _ev.player = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_running:
        break;
    case ggpo_eventcode_connection_interrupted:
        _ev.player = buffer_read(_fb, buffer_s32);
        _ev.disconnect_timeout = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_connection_resumed:
        _ev.player = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_disconnected_from_peer:
        _ev.player = buffer_read(_fb, buffer_s32);
        break;
    case ggpo_eventcode_timesync:
        _ev.frames_ahead = buffer_read(_fb, buffer_s32);
        break;
}
ggpo_on_event(_ev);

#define ggpo_gml_prepare_buffer
/// (size:int)->buffer~
var _size = argument0;
gml_pragma("global", "global.__ggpo_gml_buffer = undefined");
var _buf = global.__ggpo_gml_buffer;
if (_buf == undefined) {
    _buf = buffer_create(_size, buffer_grow, 1);
    global.__ggpo_gml_buffer = _buf;
} else if (buffer_get_size(_buf) < _size) {
    buffer_resize(_buf, _size);
}
buffer_seek(_buf, buffer_seek_start, 0);
return _buf;