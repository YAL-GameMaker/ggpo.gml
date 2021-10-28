#include "stdafx.h"

int ggpo_disconnect_flags = 0x0;
dllg bool ggpo_player_is_active(int player_number) {
	return (ggpo_disconnect_flags & (1 << player_number)) == 0;
}

char ggpo_game_name[256] = "ggpo.gml";
dllx void ggpo_set_game_name(const char* name) {
	strncpy(ggpo_game_name, name, std::size(ggpo_game_name));
}

int ggpo_input_size = 64;
dllg void ggpo_set_input_size(int size) {
	ggpo_input_size = size;
}


dllg int ggpo_start_session(int num_players, uint16_t local_port) {
	ggpo_disconnect_flags = 0x0;
	auto cbs = ggpo_get_callbacks();
	return ggpo_start_session(&ggpo, &cbs, ggpo_game_name, num_players, ggpo_input_size, local_port);
}

dllg int ggpo_start_spectating(int num_players, uint16_t local_port, const char* host_ip, uint16_t host_port) {
	ggpo_disconnect_flags = 0x0;
	auto cbs = ggpo_get_callbacks();
	return ggpo_start_spectating(&ggpo, &cbs, ggpo_game_name, num_players, ggpo_input_size, local_port, (char*)host_ip, host_port);
}

dllg int ggpo_start_synctest(int num_players, int frames) {
	ggpo_disconnect_flags = 0x0;
	auto cbs = ggpo_get_callbacks();
	return ggpo_start_synctest(&ggpo, &cbs, ggpo_game_name, num_players, ggpo_input_size, frames);
}


dllg int ggpo_close_session() {
	return ggpo_close_session(ggpo);
}


dllg optional<int> ggpo_add_local_player(int player_num) {
	GGPOPlayer player{};
	player.size = sizeof player;
	player.player_num = player_num;
	player.type = GGPOPlayerType::GGPO_PLAYERTYPE_LOCAL;
	GGPOPlayerHandle handle;
	ggpoLastError = ggpo_add_player(ggpo, &player, &handle);
	if (GGPO_SUCCEEDED(ggpoLastError)) {
		return handle;
	} else return {};
}
dllg optional<int> ggpo_add_remote_player(int player_num, const char* ip, uint16_t port) {
	GGPOPlayer player{};
	player.size = sizeof player;
	player.player_num = player_num;
	player.type = GGPOPlayerType::GGPO_PLAYERTYPE_REMOTE;
	auto& remote = player.u.remote;
	strncpy(remote.ip_address, ip, std::size(remote.ip_address));
	remote.port = port;
	GGPOPlayerHandle handle;
	ggpoLastError = ggpo_add_player(ggpo, &player, &handle);
	if (GGPO_SUCCEEDED(ggpoLastError)) {
		return handle;
	} else return {};
}

dllg int ggpo_disconnect_player(int player_handle) {
	return ggpo_disconnect_player(ggpo, player_handle);
}

dllg int ggpo_set_frame_delay(int player_handle, int frame_delay) {
	return ggpo_set_frame_delay(ggpo, player_handle, frame_delay);
}

dllg int ggpo_add_local_input(int player_handle, gml_buffer buf, std::optional<int> size = {}) {
	int _size = size.has_value() ? size.value() : buf.tell();
	return ggpo_add_local_input(ggpo, player_handle, buf.data(), _size);
}

dllg int ggpo_synchronize_input(gml_buffer buf) {
	return ggpo_synchronize_input(ggpo, buf.data(), buf.size(), &ggpo_disconnect_flags);
}