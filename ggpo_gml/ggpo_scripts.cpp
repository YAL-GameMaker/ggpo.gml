#include "ggpo_scripts.h"

ggpo_scripts scripts;
uint8_t* ggpo_fixed_buffer;
dllg int ggpo_preinit_2(
	gml_asset_index_of ggpo_do_game_begin_2,
	gml_asset_index_of ggpo_do_advance_frame_2,
	gml_asset_index_of ggpo_do_game_state_save_2,
	gml_asset_index_of ggpo_do_game_state_load_2,
	gml_asset_index_of ggpo_do_game_state_free_2,
	gml_asset_index_of ggpo_do_game_state_dump_2,
	gml_asset_index_of ggpo_do_event_2,
	gml_asset_index_of ggpo_do_network_create_socket,
	gml_asset_index_of ggpo_do_network_destroy_socket,
	gml_asset_index_of ggpo_do_network_send_packet_1,
	gml_asset_index_of ggpo_do_network_receive_packet,
	gml_buffer fixed_buffer
) {
	ggpo_fixed_buffer = fixed_buffer.data();
	#define X(id) {\
		if (id < 0) trace(#id " is missing!");\
		scripts.id = id;\
	}
	
	X(ggpo_do_game_begin_2);
	X(ggpo_do_advance_frame_2);
	X(ggpo_do_game_state_save_2);
	X(ggpo_do_game_state_load_2);
	X(ggpo_do_game_state_free_2);
	X(ggpo_do_game_state_dump_2);
	X(ggpo_do_event_2);
	X(ggpo_do_network_create_socket);
	X(ggpo_do_network_destroy_socket);
	X(ggpo_do_network_send_packet_1);
	X(ggpo_do_network_receive_packet);
	return 1;
}
