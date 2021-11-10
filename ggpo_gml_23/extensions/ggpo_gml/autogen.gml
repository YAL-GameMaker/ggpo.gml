#define ggpo_do_game_state_save_3
/// ggpo_do_game_state_save_3(buf:buffer)
var _buf = ggpo_gml_prepare_buffer(8);
var _val_0 = argument0;
if (buffer_exists(_val_0)) {
	buffer_write(_buf, buffer_u64, int64(buffer_get_address(_val_0)));
	buffer_write(_buf, buffer_s32, buffer_get_size(_val_0));
	buffer_write(_buf, buffer_s32, buffer_tell(_val_0));
} else {
	buffer_write(_buf, buffer_u64, 0);
	buffer_write(_buf, buffer_s32, 0);
	buffer_write(_buf, buffer_s32, 0);
}
ggpo_do_game_state_save_3_raw(buffer_get_address(_buf));

#define ggpo_idle
/// ggpo_idle(timeout_ms:int)->int
var _buf = ggpo_gml_prepare_buffer(4);
buffer_write(_buf, buffer_s32, argument0);
return ggpo_idle_raw(buffer_get_address(_buf));

#define ggpo_advance_frame
/// ggpo_advance_frame()->int
var _buf = ggpo_gml_prepare_buffer(1);
return ggpo_advance_frame_raw(buffer_get_address(_buf));

#define ggpo_player_is_active
/// ggpo_player_is_active(player_number:int)->bool
var _buf = ggpo_gml_prepare_buffer(4);
buffer_write(_buf, buffer_s32, argument0);
return ggpo_player_is_active_raw(buffer_get_address(_buf));

#define ggpo_set_input_size
/// ggpo_set_input_size(size:int)
var _buf = ggpo_gml_prepare_buffer(4);
buffer_write(_buf, buffer_s32, argument0);
ggpo_set_input_size_raw(buffer_get_address(_buf));

#define ggpo_start_session
/// ggpo_start_session(num_players:int, local_port:int)->int
var _buf = ggpo_gml_prepare_buffer(6);
buffer_write(_buf, buffer_s32, argument0);
buffer_write(_buf, buffer_u16, argument1);
return ggpo_start_session_raw(buffer_get_address(_buf));

#define ggpo_start_spectating
/// ggpo_start_spectating(num_players:int, local_port:int, host_ip:string, host_port:int)->int
var _buf = ggpo_gml_prepare_buffer(9);
buffer_write(_buf, buffer_s32, argument0);
buffer_write(_buf, buffer_u16, argument1);
buffer_write(_buf, buffer_u16, argument3);
return ggpo_start_spectating_raw(buffer_get_address(_buf), argument2);

#define ggpo_start_synctest
/// ggpo_start_synctest(num_players:int, frames:int)->int
var _buf = ggpo_gml_prepare_buffer(8);
buffer_write(_buf, buffer_s32, argument0);
buffer_write(_buf, buffer_s32, argument1);
return ggpo_start_synctest_raw(buffer_get_address(_buf));

#define ggpo_close_session
/// ggpo_close_session()->int
var _buf = ggpo_gml_prepare_buffer(1);
return ggpo_close_session_raw(buffer_get_address(_buf));

#define ggpo_add_local_player
/// ggpo_add_local_player(player_num:int)->int?
var _buf = ggpo_gml_prepare_buffer(5);
buffer_write(_buf, buffer_s32, argument0);
if (ggpo_add_local_player_raw(buffer_get_address(_buf))) {
	buffer_seek(_buf, buffer_seek_start, 0);
	var _val_0;
	if (buffer_read(_buf, buffer_bool)) {
		_val_0 = buffer_read(_buf, buffer_s32);
	} else _val_0 = undefined;
	return _val_0;
} else return undefined;

#define ggpo_add_remote_player
/// ggpo_add_remote_player(player_num:int, ip:string, port:int)->int?
var _buf = ggpo_gml_prepare_buffer(7);
buffer_write(_buf, buffer_s32, argument0);
buffer_write(_buf, buffer_u16, argument2);
if (ggpo_add_remote_player_raw(buffer_get_address(_buf), argument1)) {
	buffer_seek(_buf, buffer_seek_start, 0);
	var _val_0;
	if (buffer_read(_buf, buffer_bool)) {
		_val_0 = buffer_read(_buf, buffer_s32);
	} else _val_0 = undefined;
	return _val_0;
} else return undefined;

#define ggpo_disconnect_player
/// ggpo_disconnect_player(player_handle:int)->int
var _buf = ggpo_gml_prepare_buffer(4);
buffer_write(_buf, buffer_s32, argument0);
return ggpo_disconnect_player_raw(buffer_get_address(_buf));

#define ggpo_set_frame_delay
/// ggpo_set_frame_delay(player_handle:int, frame_delay:int)->int
var _buf = ggpo_gml_prepare_buffer(8);
buffer_write(_buf, buffer_s32, argument0);
buffer_write(_buf, buffer_s32, argument1);
return ggpo_set_frame_delay_raw(buffer_get_address(_buf));

#define ggpo_add_local_input
/// ggpo_add_local_input(player_handle:int, buf:buffer, ?size:int?)->int
var _buf = ggpo_gml_prepare_buffer(17);
buffer_write(_buf, buffer_s32, argument[0]);
var _val_0 = argument[1];
if (buffer_exists(_val_0)) {
	buffer_write(_buf, buffer_u64, int64(buffer_get_address(_val_0)));
	buffer_write(_buf, buffer_s32, buffer_get_size(_val_0));
	buffer_write(_buf, buffer_s32, buffer_tell(_val_0));
} else {
	buffer_write(_buf, buffer_u64, 0);
	buffer_write(_buf, buffer_s32, 0);
	buffer_write(_buf, buffer_s32, 0);
}
if (argument_count >= 3) {
	buffer_write(_buf, buffer_bool, true);
	var _val_0 = argument[2];
	buffer_write(_buf, buffer_bool, _val_0 != undefined);
	if (_val_0 != undefined) {
		buffer_write(_buf, buffer_s32, _val_0);
	}
} else buffer_write(_buf, buffer_bool, false);
return ggpo_add_local_input_raw(buffer_get_address(_buf));

#define ggpo_synchronize_input
/// ggpo_synchronize_input(buf:buffer)->int
var _buf = ggpo_gml_prepare_buffer(8);
var _val_0 = argument0;
if (buffer_exists(_val_0)) {
	buffer_write(_buf, buffer_u64, int64(buffer_get_address(_val_0)));
	buffer_write(_buf, buffer_s32, buffer_get_size(_val_0));
	buffer_write(_buf, buffer_s32, buffer_tell(_val_0));
} else {
	buffer_write(_buf, buffer_u64, 0);
	buffer_write(_buf, buffer_s32, 0);
	buffer_write(_buf, buffer_s32, 0);
}
return ggpo_synchronize_input_raw(buffer_get_address(_buf));

#define ggpo_preinit_2
/// ggpo_preinit_2(fixed_buffer:buffer)->int
var _buf = ggpo_gml_prepare_buffer(52);
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_game_begin_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_advance_frame_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_game_state_save_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_game_state_load_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_game_state_free_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_game_state_dump_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_event_2"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_network_create_socket"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_network_destroy_socket"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_network_send_packet_1"));
buffer_write(_buf, buffer_s32, asset_get_index("ggpo_do_network_receive_packet"));
var _val_0 = argument0;
if (buffer_exists(_val_0)) {
	buffer_write(_buf, buffer_u64, int64(buffer_get_address(_val_0)));
	buffer_write(_buf, buffer_s32, buffer_get_size(_val_0));
	buffer_write(_buf, buffer_s32, buffer_tell(_val_0));
} else {
	buffer_write(_buf, buffer_u64, 0);
	buffer_write(_buf, buffer_s32, 0);
	buffer_write(_buf, buffer_s32, 0);
}
return ggpo_preinit_2_raw(buffer_get_address(_buf));

