/// @author YellowAfterlife

#include "stdafx.h"
#include "script_execute.h"
//#include "ggponet.h"
#include "ggpo_scripts.h"

#include <chrono>
#include <thread>

GGPOSession* ggpo = nullptr;
GGPOErrorCode ggpoLastError = GGPO_OK;
/// ->ggpo_errorcode
dllx double ggpo_get_last_error() {
	return ggpoLastError;
}

static bool canAccessMemory(const void* base, size_t size) {
	#ifdef _GGPO_MEMCHECK
	const auto pmask = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY
		| PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
	::MEMORY_BASIC_INFORMATION mbi{};
	size_t steps = size > 0 ? 2 : 1;
	for (auto step = 0u; step < steps; step++) {
		const void* addr = ((uint8_t*)base) + step * (size - 1);
		if (!VirtualQuery(addr, &mbi, sizeof mbi)) return false;
		if (mbi.State != MEM_COMMIT) return false;
		if ((mbi.Protect & PAGE_GUARD) != 0) return false;
		if ((mbi.Protect & pmask) == 0) return false;
}
	#endif
	return true;
}
static int findCScriptRefOffset(uint8_t* _f1, uint8_t* _f2) {
	auto f1 = (void**)_f1;
	auto f2 = (void**)_f2;
	void** fx[] = { f1, f2 };
	#ifdef _GGPO_MEMCHECK
	::MEMORY_BASIC_INFORMATION mbi{};
	const auto pExec = PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
	#endif
	for (auto i = 10u; i < 24; i++) {
		auto step = 0u;
		for (; step < 2; step++) {
			auto fi = fx[step];
			if (!canAccessMemory(fi + i - 1, sizeof(void*) * 3)) return -1;

			// should be NULL, <addr>, NULL
			if (fi[i - 1] != nullptr) break;
			if (fi[i] == nullptr) break;
			if (fi[i + 1] != nullptr) break;
			//trace("ind %d step %u: %p %p %p", i, step, *prev, *curr, *next);
		}
		if (step < 2u) continue;

		// destination address must match:
		auto dest = f1[i];
		if (dest != f2[i]) continue;

		#ifdef _GGPO_MEMCHECK
		// destination address must be executable:
		if (!VirtualQuery(dest, &mbi, sizeof mbi)) continue;
		if ((mbi.Protect & pExec) == 0) continue;
		#endif

		return (int)(sizeof(void*) * i);
	}
	return -1;
}

dllx double ggpo_preinit_1(GMLClosure* _script_execute, GMLClosure* _script_execute_alt) {
	#ifndef GML_SOCKETS
	WSADATA wd = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wd);
	#endif
	auto ofs = findCScriptRefOffset((uint8_t*)_script_execute, (uint8_t*)_script_execute_alt);
	if (ofs < 0) return -1;
	script_execute::self = _script_execute;
	script_execute::raw = *(GMLFunc**)((uint8_t*)_script_execute + ofs);
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
	std::this_thread::sleep_for(std::chrono::milliseconds((int)amt));
	return true;
}

dllg int ggpo_idle(int timeout_ms) {
	return ggpo_idle(ggpo, timeout_ms);
}

dllg int ggpo_advance_frame() {
	return ggpo_advance_frame(ggpo);
}