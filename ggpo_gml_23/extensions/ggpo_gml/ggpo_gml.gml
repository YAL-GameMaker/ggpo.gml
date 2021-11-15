#define ggpo_preinit
//#global ggpo_gml_is_js
var _js = (os_browser != browser_not_a_browser);
ggpo_gml_is_js = _js;

// on JS, we have to wait until the WASM blob is loaded...
if (!_js) gmcallback_ggpo_preinit();

#define gmcallback_ggpo_preinit
var _js = ggpo_gml_is_js;
global.__ggpo_script_execute = method(undefined, script_execute);
global.__ggpo_script_execute_ptr = _js ? undefined : ptr(global.__ggpo_script_execute);
global.__ggpo_fixed_buffer = buffer_create(ggpo_fixed_buffer_size, buffer_fixed, 1);
switch (ggpo_preinit_1(global.__ggpo_script_execute_ptr, 256)) {
    case 1:
        ggpo_preinit_2(_js ? -1 : global.__ggpo_fixed_buffer);
        if (_js) {
            ggpo_gml_wasm_exec_init(global.__ggpo_script_execute);
            ggpo_gml_wasm_init_fixed_buffer(buffer_get_address(global.__ggpo_fixed_buffer), ggpo_fixed_buffer_size);
            if (!_js) gmcallback_ggpo_gml_script_execute(0, 0, 0, 0, 0, 0, 0, 0);
        }
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

//#global ggpo_on_network_create_socket
ggpo_on_network_create_socket = asset_get_index("ggpo_default_network_create_socket");
//#global ggpo_on_network_destroy_socket
ggpo_on_network_destroy_socket = asset_get_index("ggpo_default_network_destroy_socket");
//#global ggpo_on_network_send_packet
ggpo_on_network_send_packet = asset_get_index("ggpo_default_network_send_packet");
//#global ggpo_on_network_receive_packet
ggpo_on_network_receive_packet = asset_get_index("ggpo_default_network_receive_packet");

global.__ggpo_do_network_receive_packet__active = false;
global.__ggpo_do_network_receive_packet__size = false;
global.__ggpo_default_packet_queue = ds_map_create(); /// @is {ds_map<network_socket, ds_queue<[ip:string, port:int, data:buffer, size:int]>>}
global.__ggpo_default_packet_pool = ds_queue_create(); /// @is {ds_queue<buffer>}
global.__ggpo_default_verbose = false;

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
//show_debug_message(ggpo_eventcode_get_name(_ev.code) + ": " + string(_ev));
if (_ev.code == ggpo_eventcode_timesync) {
    ggpo_sleep(_ev.frames_ahead * game_get_speed(gamespeed_microseconds) / 1000)
}

#define ggpo_default_network_create_socket
var _bind_port = argument0, _retries = argument1;
if (global.__ggpo_default_verbose) show_debug_message({ func: "ggpo_default_network_create_socket", port: _bind_port, retries: _retries });
for (var _port = _bind_port; _port <= _bind_port + _retries; _port++) {
    var _socket = network_create_socket_ext(network_socket_udp, _port);
    if (global.__ggpo_default_verbose) show_debug_message("Socket OK! Port: " + string(_port));
    if (_socket >= 0) {
        global.__ggpo_default_packet_queue[?_socket] = ds_queue_create();
        return _socket;
    }
}
if (global.__ggpo_default_verbose) show_debug_message("Failed to bind a socket!");
return -1;

#define ggpo_default_network_destroy_socket
var _socket = argument0;
if (global.__ggpo_default_verbose) show_debug_message({ func: "ggpo_default_network_destroy_socket", socket: _socket });
network_destroy(_socket);
var _queue = global.__ggpo_default_packet_queue[?_socket];
if (_queue != undefined) {
    while (!ds_queue_empty(_queue)) {
        var _item = ds_queue_dequeue(_queue);
        ds_queue_enqueue(global.__ggpo_default_packet_pool, _item[2]);
    }
    ds_queue_destroy(_queue);
    ds_map_delete(global.__ggpo_default_packet_queue, _socket);
}

#define ggpo_default_network_send_packet
var _socket = argument0, _url = argument1, _port = argument2, _buf = argument3, _len = argument4;
if (global.__ggpo_default_verbose) show_debug_message({ func: "ggpo_default_network_send_packet", socket: _socket, ip: _url, port: _port, size: _len });
return network_send_udp(_socket, _url, _port, _buf, _len);

#define ggpo_default_network_receive_packet
var _socket = argument0;
var _queue = global.__ggpo_default_packet_queue[?_socket];
if (_queue == undefined || ds_queue_empty(_queue)) return -1;
//trace("recv", _socket, _queue, _queue != undefined ? ds_queue_size(_queue) : -1)
var _packet = ds_queue_dequeue(_queue);
if (global.__ggpo_default_verbose) show_debug_message({ func: "ggpo_default_network_receive_packet", ip: _packet[0], port: _packet[1], size: _packet[3] });
ggpo_network_packet_receive(_packet[0], _packet[1], _packet[2], _packet[3]);
ds_queue_enqueue(global.__ggpo_default_packet_pool, _packet[2]); // GML isn't multi-threaded so no one's going to write anything to this before we return

#define ggpo_default_async_network
/// (?async_load)
var _e/*:async_load_network*/ = argument_count > 0 ? argument[0] : /*#cast*/ async_load;
if (_e[?"type"] != network_type_data) exit;
var _socket = _e[?"id"];
var _queue = global.__ggpo_default_packet_queue[?_socket];
if (_queue == undefined) exit;
var _size = _e[?"size"];
var _buf/*:buffer*/;
if (ds_queue_empty(global.__ggpo_default_packet_pool)) {
    _buf = buffer_create(4096, buffer_grow, 1);
} else {
    _buf = ds_queue_dequeue(global.__ggpo_default_packet_pool);
    if (buffer_get_size(_buf) < _size) buffer_resize(_buf, _size);
}
buffer_copy(_e[?"buffer"], 0, _size, _buf, 0);
if (global.__ggpo_default_verbose) show_debug_message({ queue: _queue, func: "ggpo_default_async_network", socket: _socket, ip: _e[?"ip"], port: _e[?"port"], size: _size });
ds_queue_enqueue(_queue, [_e[?"ip"], _e[?"port"], _buf, _size]);

#define ggpo_do_game_state_save_2
// (frame)
var _buf = buffer_create(ggpo_game_state_base_size, buffer_grow, 1);
ggpo_on_game_state_save(_buf, argument0);
if (ggpo_gml_is_js) {
    // hacky: have to do manual memory management for WASM's copy
    var _tell = buffer_tell(_buf);
    var _wbuf = ggpo_gml_wasm_alloc(_tell, buffer_get_address(_buf));
    var _args = ggpo_gml_prepare_buffer(16);
    buffer_write(_args, buffer_u64, _wbuf);
    buffer_write(_args, buffer_s32, buffer_get_size(_buf));
    buffer_write(_args, buffer_s32, _tell);
    global.__ggpo_game_state_buffers[?_wbuf] = _buf;
    ggpo_do_game_state_save_3_raw(buffer_get_address(_args), 16);
} else {
    global.__ggpo_game_state_buffers[?int64(buffer_get_address(_buf))] = _buf;
    ggpo_do_game_state_save_3(_buf);
}

#define ggpo_do_game_state_load_2
// (addr, len)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) {
    show_debug_message("ggpo_do_game_state_load_2: no buffer for " + string(argument0));
    return false;
}
buffer_seek(_buf, buffer_seek_start, 0);
ggpo_on_game_state_load(_buf, argument1);
return true;

#define ggpo_do_game_state_dump_2
// (addr, len)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) {
    show_debug_message("ggpo_do_game_state_dump_2: no buffer for " + string(argument0));
    return false;
}
var _fb = global.__ggpo_fixed_buffer;
buffer_seek(_fb, buffer_seek_start, 0);
if (ggpo_gml_is_js) ggpo_gml_wasm_get_fixed_buffer();
var _name = buffer_read(_fb, buffer_string);
var _result = ggpo_on_game_state_dump(_buf, _name, argument1);
return _result == undefined || _result;

#define ggpo_do_game_state_free_2
// (addr)
var _buf = global.__ggpo_game_state_buffers[?argument0];
if (_buf == undefined) {
    show_debug_message("ggpo_do_game_state_free_2: no buffer for " + string(argument0));
    return false;
}
if (ggpo_gml_is_js) ggpo_gml_wasm_free(argument0);
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
if (ggpo_gml_is_js) ggpo_gml_wasm_get_fixed_buffer();
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

#define ggpo_do_network_create_socket
var _bind_port = argument0, _retries = argument1;
var _socket = ggpo_on_network_create_socket(_bind_port, _retries);
if (!is_numeric(_socket)) show_error("ggpo_on_network_create_socket should return a socket ID or -1", 1);
return _socket;

#define ggpo_do_network_destroy_socket
var _socket = argument0;
ggpo_on_network_destroy_socket(_socket);

#define ggpo_do_network_send_packet_1
var _socket = argument0, _len = argument1;
var _buf = ggpo_gml_prepare_buffer(_len);
ggpo_do_network_send_packet_2(buffer_get_address(_buf), _len);
var _args = global.__ggpo_fixed_buffer;
if (ggpo_gml_is_js) ggpo_gml_wasm_get_fixed_buffer();
buffer_seek(_args, buffer_seek_start, 0);
var _url = ggpo_buffer_read_chars(_args, 64);
var _port = buffer_read(_args, buffer_s32);
return ggpo_on_network_send_packet(_socket, _url, _port, _buf, _len);

#define ggpo_do_network_receive_packet
var _socket = argument0;
var _was = global.__ggpo_do_network_receive_packet__active;
global.__ggpo_do_network_receive_packet__active = true;
global.__ggpo_do_network_receive_packet__size = -1;
ggpo_on_network_receive_packet(_socket);
global.__ggpo_do_network_receive_packet__active = _was;
return global.__ggpo_do_network_receive_packet__size;

#define ggpo_network_packet_receive
/// (url:string, port:int, buffer:buffer, size:int)
var _ip/*:string*/ = argument0, _port/*:int*/ = argument1, _buffer/*:buffer*/ = argument2, _size/*:int*/ = argument3;
if (global.__ggpo_do_network_receive_packet__active) {
    var _args = global.__ggpo_fixed_buffer;
    buffer_seek(_args, buffer_seek_start, 0);
    if (ggpo_gml_is_js) {
        buffer_write(_args, buffer_u64, ggpo_gml_wasm_alloc(_size, buffer_get_address(_buffer)));
    } else {
        buffer_write(_args, buffer_u64, int64(buffer_get_address(_buffer)));
    }
    ggpo_buffer_write_chars(_args, _ip, 64);
    buffer_write(_args, buffer_s32, _port);
    if (ggpo_gml_is_js) ggpo_gml_wasm_set_fixed_buffer();
    global.__ggpo_do_network_receive_packet__size = _size;
    return _size;
} else show_error("ggpo_packet_received can only be called inside ggpo_on_network_receive_packet", 1);

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

#define ggpo_buffer_read_chars
/// (buffer:buffer, len:int)->string
var _buf = argument0, _len = argument1;
gml_pragma("global", "global.__ggpo_string_buffer = undefined");
var _tmp = global.__ggpo_string_buffer;
if (_tmp == undefined) {
    _tmp = buffer_create(_len + 1, buffer_grow, 1);
    global.__ggpo_string_buffer = _tmp;
} else if (buffer_get_size(_tmp) <= _len) {
    buffer_resize(_tmp, _len + 1);
}
buffer_copy(_buf, buffer_tell(_buf), _len, _tmp, 0);
buffer_seek(_buf, buffer_seek_relative, _len);
buffer_poke(_tmp, _len, buffer_u8, 0);
buffer_seek(_tmp, buffer_seek_start, 0);
return buffer_read(_tmp, buffer_string);

#define ggpo_buffer_write_chars
/// (buffer:buffer, str:string, len:int)
var _buf = argument0, _str = argument1, _len = argument2;
var _tmp = global.__ggpo_string_buffer;
if (_tmp == undefined) {
    _tmp = buffer_create(_len + 1, buffer_grow, 1);
    global.__ggpo_string_buffer = _tmp;
}
buffer_seek(_tmp, buffer_seek_start, 0);
buffer_write(_tmp, buffer_text, _str);
var _pos = buffer_tell(_tmp);
if (_pos < _len) buffer_fill(_tmp, _pos, buffer_u8, 0, _len - _pos);
buffer_copy(_tmp, 0, _len, _buf, buffer_tell(_buf));
buffer_seek(_buf, buffer_seek_relative, _len);

#define gmcallback_ggpo_gml_script_execute
return script_execute(argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7);