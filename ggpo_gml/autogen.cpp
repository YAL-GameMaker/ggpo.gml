#include "gml_ext.h"
extern void ggpo_do_game_state_save_3(gml_buffer buf);
dllx double ggpo_do_game_state_save_3_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	gml_buffer _arg_buf;
	_arg_buf = _in.read_gml_buffer();
	ggpo_do_game_state_save_3(_arg_buf);
	return 1;
}

extern int ggpo_idle(int timeout_ms);
dllx double ggpo_idle_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_timeout_ms;
	_arg_timeout_ms = _in.read<int>();
	return ggpo_idle(_arg_timeout_ms);
}

extern int ggpo_advance_frame();
dllx double ggpo_advance_frame_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	return ggpo_advance_frame();
}

extern bool ggpo_player_is_active(int player_number);
dllx double ggpo_player_is_active_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_player_number;
	_arg_player_number = _in.read<int>();
	return ggpo_player_is_active(_arg_player_number);
}

extern void ggpo_set_input_size(int size);
dllx double ggpo_set_input_size_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_size;
	_arg_size = _in.read<int>();
	ggpo_set_input_size(_arg_size);
	return 1;
}

extern int ggpo_start_session(int num_players, uint16_t local_port);
dllx double ggpo_start_session_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_num_players;
	_arg_num_players = _in.read<int>();
	uint16_t _arg_local_port;
	_arg_local_port = _in.read<uint16_t>();
	return ggpo_start_session(_arg_num_players, _arg_local_port);
}

extern int ggpo_start_spectating(int num_players, uint16_t local_port, const char* host_ip, uint16_t host_port);
dllx double ggpo_start_spectating_raw(void* _in_ptr, double _in_ptr_size, char* _arg_host_ip) {
	gml_istream _in(_in_ptr);
	int _arg_num_players;
	_arg_num_players = _in.read<int>();
	uint16_t _arg_local_port;
	_arg_local_port = _in.read<uint16_t>();
	uint16_t _arg_host_port;
	_arg_host_port = _in.read<uint16_t>();
	return ggpo_start_spectating(_arg_num_players, _arg_local_port, _arg_host_ip, _arg_host_port);
}

extern int ggpo_start_synctest(int num_players, int frames);
dllx double ggpo_start_synctest_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_num_players;
	_arg_num_players = _in.read<int>();
	int _arg_frames;
	_arg_frames = _in.read<int>();
	return ggpo_start_synctest(_arg_num_players, _arg_frames);
}

extern int ggpo_close_session();
dllx double ggpo_close_session_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	return ggpo_close_session();
}

extern optional<int> ggpo_add_local_player(int player_num);
dllx double ggpo_add_local_player_raw(void* _inout_ptr, double _inout_ptr_size) {
	gml_istream _in(_inout_ptr);
	int _arg_player_num;
	_arg_player_num = _in.read<int>();
	optional<int> _ret = ggpo_add_local_player(_arg_player_num);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern optional<int> ggpo_add_remote_player(int player_num, const char* ip, uint16_t port);
dllx double ggpo_add_remote_player_raw(void* _inout_ptr, double _inout_ptr_size, char* _arg_ip) {
	gml_istream _in(_inout_ptr);
	int _arg_player_num;
	_arg_player_num = _in.read<int>();
	uint16_t _arg_port;
	_arg_port = _in.read<uint16_t>();
	optional<int> _ret = ggpo_add_remote_player(_arg_player_num, _arg_ip, _arg_port);
	gml_ostream _out(_inout_ptr);
	{
		auto& _opt = _ret;
		if (_opt.has_value()) {
			_out.write<bool>(true);
			_out.write<int>(_opt.value());
			
		} else _out.write<bool>(false);
		
	}
	return 1;
}

extern int ggpo_disconnect_player(int player_handle);
dllx double ggpo_disconnect_player_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_player_handle;
	_arg_player_handle = _in.read<int>();
	return ggpo_disconnect_player(_arg_player_handle);
}

extern int ggpo_set_frame_delay(int player_handle, int frame_delay);
dllx double ggpo_set_frame_delay_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_player_handle;
	_arg_player_handle = _in.read<int>();
	int _arg_frame_delay;
	_arg_frame_delay = _in.read<int>();
	return ggpo_set_frame_delay(_arg_player_handle, _arg_frame_delay);
}

extern int ggpo_add_local_input(int player_handle, gml_buffer buf, std::optional<int> size);
dllx double ggpo_add_local_input_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	int _arg_player_handle;
	_arg_player_handle = _in.read<int>();
	gml_buffer _arg_buf;
	_arg_buf = _in.read_gml_buffer();
	std::optional<int> _arg_size;
	if (_in.read<bool>()) {
		_arg_size = _in.read_optional<int>();
	} else _arg_size = {};
	return ggpo_add_local_input(_arg_player_handle, _arg_buf, _arg_size);
}

extern int ggpo_synchronize_input(gml_buffer out_buffer);
dllx double ggpo_synchronize_input_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	gml_buffer _arg_out_buffer;
	_arg_out_buffer = _in.read_gml_buffer();
	return ggpo_synchronize_input(_arg_out_buffer);
}

extern int ggpo_preinit_2(gml_asset_index_of ggpo_do_game_begin_2, gml_asset_index_of ggpo_do_advance_frame_2, gml_asset_index_of ggpo_do_game_state_save_2, gml_asset_index_of ggpo_do_game_state_load_2, gml_asset_index_of ggpo_do_game_state_free_2, gml_asset_index_of ggpo_do_game_state_dump_2, gml_asset_index_of ggpo_do_event_2, gml_asset_index_of ggpo_do_network_create_socket, gml_asset_index_of ggpo_do_network_destroy_socket, gml_asset_index_of ggpo_do_network_send_packet_1, gml_asset_index_of ggpo_do_network_receive_packet, gml_buffer fixed_buffer);
dllx double ggpo_preinit_2_raw(void* _in_ptr, double _in_ptr_size) {
	gml_istream _in(_in_ptr);
	gml_asset_index_of _arg_ggpo_do_game_begin_2;
	_arg_ggpo_do_game_begin_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_advance_frame_2;
	_arg_ggpo_do_advance_frame_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_game_state_save_2;
	_arg_ggpo_do_game_state_save_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_game_state_load_2;
	_arg_ggpo_do_game_state_load_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_game_state_free_2;
	_arg_ggpo_do_game_state_free_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_game_state_dump_2;
	_arg_ggpo_do_game_state_dump_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_event_2;
	_arg_ggpo_do_event_2 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_network_create_socket;
	_arg_ggpo_do_network_create_socket = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_network_destroy_socket;
	_arg_ggpo_do_network_destroy_socket = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_network_send_packet_1;
	_arg_ggpo_do_network_send_packet_1 = (gml_asset_index_of)_in.read<int32_t>();
	gml_asset_index_of _arg_ggpo_do_network_receive_packet;
	_arg_ggpo_do_network_receive_packet = (gml_asset_index_of)_in.read<int32_t>();
	gml_buffer _arg_fixed_buffer;
	_arg_fixed_buffer = _in.read_gml_buffer();
	return ggpo_preinit_2(_arg_ggpo_do_game_begin_2, _arg_ggpo_do_advance_frame_2, _arg_ggpo_do_game_state_save_2, _arg_ggpo_do_game_state_load_2, _arg_ggpo_do_game_state_free_2, _arg_ggpo_do_game_state_dump_2, _arg_ggpo_do_event_2, _arg_ggpo_do_network_create_socket, _arg_ggpo_do_network_destroy_socket, _arg_ggpo_do_network_send_packet_1, _arg_ggpo_do_network_receive_packet, _arg_fixed_buffer);
}

