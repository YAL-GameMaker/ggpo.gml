/// @author YellowAfterlife

#include "stdafx.h"
#include "script_execute.h"
//#include "ggponet.h"
#include "ggpo_scripts.h"

GGPOSession* ggpo = nullptr;
GGPOErrorCode ggpoLastError = GGPO_OK;
/// ->ggpo_errorcode
dllx double ggpo_get_last_error() {
	return ggpoLastError;
}

dllx double ggpo_preinit_1(GMLClosure* _script_execute) {
	WSADATA wd = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wd);
	script_execute::self = _script_execute;
	script_execute::raw = _script_execute->func;
	return 1;
}

///
#define ggpo_ok 0
/// NB! Matches GGPOErrorCode, but doesn't include GGPO_OK
enum class ggpo_errorcode : int{
	success = 0,
	general_failure = -1,
	invalid_session = 1,
	invalid_player_handle = 2,
	player_out_of_range = 3,
	prediction_threshold = 4,
	unsupported = 5,
	not_synchronized = 6,
	in_rollback = 7,
	input_dropped = 8,
	player_disconnected = 9,
	too_many_spectators = 10,
	invalid_request = 11,
};
dllx const char* ggpo_errorcode_get_name(double errorcode) {
	switch ((ggpo_errorcode)(int)errorcode) {
		case ggpo_errorcode::success: return "success";
		case ggpo_errorcode::general_failure: return "general_failure";
		case ggpo_errorcode::invalid_session: return "invalid_session";
		case ggpo_errorcode::invalid_player_handle: return "invalid_player_handle";
		case ggpo_errorcode::player_out_of_range: return "player_out_of_range";
		case ggpo_errorcode::prediction_threshold: return "prediction_threshold";
		case ggpo_errorcode::unsupported: return "unsupported";
		case ggpo_errorcode::not_synchronized: return "not_synchronized";
		case ggpo_errorcode::in_rollback: return "in_rollback";
		case ggpo_errorcode::input_dropped: return "input_dropped";
		case ggpo_errorcode::player_disconnected: return "player_disconnected";
		case ggpo_errorcode::too_many_spectators: return "too_many_spectators";
		case ggpo_errorcode::invalid_request: return "invalid_request";
		default: return "???";
	}
}

dllx double ggpo_sleep(double amt) {
	Sleep((DWORD)amt);
	return true;
}

dllg int ggpo_idle(int timeout_ms) {
	return ggpo_idle(ggpo, timeout_ms);
}

dllg int ggpo_advance_frame() {
	return ggpo_advance_frame(ggpo);
}