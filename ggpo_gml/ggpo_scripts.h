#pragma once
#include "script_execute.h"
struct ggpo_scripts {
	gml_script_id ggpo_do_game_begin_2;
	gml_script_id ggpo_do_advance_frame_2;
	gml_script_id ggpo_do_game_state_save_2;
	gml_script_id ggpo_do_game_state_load_2;
	gml_script_id ggpo_do_game_state_free_2;
	gml_script_id ggpo_do_game_state_dump_2;
	gml_script_id ggpo_do_event_2;
	//
	gml_script_id ggpo_do_network_create_socket;
	gml_script_id ggpo_do_network_destroy_socket;
	gml_script_id ggpo_do_network_send_packet_1;
	gml_script_id ggpo_do_network_receive_packet;
};
extern ggpo_scripts scripts;
extern uint8_t* ggpo_fixed_buffer;
///
#define ggpo_fixed_buffer_size 1024

