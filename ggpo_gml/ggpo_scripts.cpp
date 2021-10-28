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
	gml_buffer fixed_buffer
) {
	ggpo_fixed_buffer = fixed_buffer.data();
	scripts.ggpo_do_game_begin_2 = ggpo_do_game_begin_2;
	scripts.ggpo_do_advance_frame_2 = ggpo_do_advance_frame_2;
	scripts.ggpo_do_game_state_save_2 = ggpo_do_game_state_save_2;
	scripts.ggpo_do_game_state_load_2 = ggpo_do_game_state_load_2;
	scripts.ggpo_do_game_state_free_2 = ggpo_do_game_state_free_2;
	scripts.ggpo_do_game_state_dump_2 = ggpo_do_game_state_dump_2;
	scripts.ggpo_do_event_2 = ggpo_do_event_2;
	return 1;
}
