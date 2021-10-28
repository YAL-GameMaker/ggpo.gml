#include "stdafx.h"
#include "ggpo_scripts.h"

bool ggpo_do_game_begin_1(const char* game) {
	scripts.ggpo_do_game_begin_2.i();
	return true;
}
bool ggpo_do_advance_frame_1(int flags) {
	scripts.ggpo_do_advance_frame_2.i();
	return true;
}

struct {
	uint8_t* data;
	int size;
} ggpo_save_game_state_tmp;
bool ggpo_do_game_state_save_1(unsigned char** buffer, int* len, int* checksum, int frame) {
	ggpo_save_game_state_tmp.data = nullptr;
	ggpo_save_game_state_tmp.size = 0;
	scripts.ggpo_do_game_state_save_2.ii(frame);
	*buffer = ggpo_save_game_state_tmp.data;
	*len = ggpo_save_game_state_tmp.size;
	return true;
}
dllg void ggpo_do_game_state_save_3(gml_buffer buf) {
	ggpo_save_game_state_tmp.data = buf.data();
	ggpo_save_game_state_tmp.size = buf.tell();
}

bool ggpo_do_game_state_load_1(uint8_t* buffer, int len) {
	scripts.ggpo_do_game_state_load_2.lii((int64_t)buffer, len);
	return true;
}

void ggpo_do_game_state_free_1(void* buffer) {
	scripts.ggpo_do_game_state_free_2.li((int64_t)buffer);
}

bool ggpo_do_game_state_dump_1(char* filename, uint8_t* buffer, int len) {
	strncpy((char*)ggpo_fixed_buffer, filename, ggpo_fixed_buffer_size);
	return scripts.ggpo_do_game_state_dump_2.lii((int64_t)buffer, len) > 0;
}

///
enum class ggpo_eventcode { // NB! sync with GGPOEventCode
	connected_to_peer            = 1000,
	synchronizing_with_peer      = 1001,
	synchronized_with_peer       = 1002,
	running                      = 1003,
	disconnected_from_peer       = 1004,
	timesync                     = 1005,
	connection_interrupted       = 1006,
	connection_resumed           = 1007,
};
dllx const char* ggpo_eventcode_get_name(double eventcode) {
	switch ((ggpo_eventcode)(int)eventcode) {
		case ggpo_eventcode::connected_to_peer: return "connected_to_peer";
		case ggpo_eventcode::synchronizing_with_peer: return "synchronizing_with_peer";
		case ggpo_eventcode::synchronized_with_peer: return "synchronized_with_peer";
		case ggpo_eventcode::running: return "running";
		case ggpo_eventcode::disconnected_from_peer: return "disconnected_from_peer";
		case ggpo_eventcode::timesync: return "timesync";
		case ggpo_eventcode::connection_interrupted: return "connection_interrupted";
		case ggpo_eventcode::connection_resumed: return "connection_resumed";
		return "???";
	}
}

bool ggpo_do_event_1(GGPOEvent* e) {
	auto& u = e->u;
	gml_ostream s(ggpo_fixed_buffer);
	s.write<int>(e->code);
	switch (e->code) {
	case GGPO_EVENTCODE_CONNECTED_TO_PEER:
		s.write<int32_t>(u.connected.player);
		break;
	case GGPO_EVENTCODE_SYNCHRONIZING_WITH_PEER:
		s.write<int32_t>(u.synchronizing.player);
		s.write<int32_t>(u.synchronizing.count);
		s.write<int32_t>(u.synchronizing.total);
		break;
	case GGPO_EVENTCODE_SYNCHRONIZED_WITH_PEER:
		s.write<int32_t>(u.synchronizing.player);
		break;
	case GGPO_EVENTCODE_RUNNING:
		break;
	case GGPO_EVENTCODE_CONNECTION_INTERRUPTED:
		s.write<int32_t>(u.connection_interrupted.player);
		s.write<int32_t>(u.connection_interrupted.disconnect_timeout);
		break;
	case GGPO_EVENTCODE_CONNECTION_RESUMED:
		s.write<int32_t>(u.connection_resumed.player);
		break;
	case GGPO_EVENTCODE_DISCONNECTED_FROM_PEER:
		s.write<int32_t>(u.disconnected.player);
		break;
	case GGPO_EVENTCODE_TIMESYNC:
		s.write<int32_t>(u.timesync.frames_ahead);
		break;
	}
	scripts.ggpo_do_event_2.i();
	return true;
}

GGPOSessionCallbacks ggpo_get_callbacks() {
	GGPOSessionCallbacks cb{};
	cb.begin_game = ggpo_do_game_begin_1;
	cb.advance_frame = ggpo_do_advance_frame_1;
	cb.save_game_state = ggpo_do_game_state_save_1;
	cb.load_game_state = ggpo_do_game_state_load_1;
	cb.log_game_state = ggpo_do_game_state_dump_1;
	cb.free_buffer = ggpo_do_game_state_free_1;
	cb.on_event = ggpo_do_event_1;
	return cb;
}