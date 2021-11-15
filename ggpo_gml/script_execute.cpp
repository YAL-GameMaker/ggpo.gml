#include "script_execute.h"

namespace script_execute {
	GMLClosure* self;
	GMLFunc* raw;
	void call(GMLVar& result, GMLVar* args, size_t argc) {
		raw(result, self, self, argc, args);
	}
}

#ifdef WASM
constexpr char fn[] = "window.gml_Script_gmcallback_ggpo_gml_script_execute";
#endif

int gml_script_id::i(int _default) {
	#ifdef WASM
	return EM_ASM_INT({
		return window.ggpo_gml_wasm_exec($0);
	}, id);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0 };
	args[0].setInt32(id);
	call(result, args);
	return result.getInt32(_default);
	#endif
}

int gml_script_id::ii(int arg0, int _default) {
	#ifdef WASM
	return EM_ASM_INT({
		return window.ggpo_gml_wasm_exec($0, $1);
		}, id, arg0);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0 };
	args[0].setInt32(id);
	args[1].setInt32(arg0);
	call(result, args);
	return result.getInt32(_default);
	#endif
}
int gml_script_id::li(int64_t arg0, int _default) {
	#ifdef WASM
	return EM_ASM_INT({
		return window.ggpo_gml_wasm_exec($0, $1);
		}, id, (double)arg0);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	call(result, args);
	return result.getInt32(_default);
	#endif
}
int64_t gml_script_id::ll(int64_t arg0, int64_t _default) {
	#ifdef WASM
	return (int64_t)EM_ASM_DOUBLE({
		return window.ggpo_gml_wasm_exec($0, $1);
		}, id, (double)arg0);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	call(result, args);
	return result.getInt64(_default);
	#endif
}

int gml_script_id::lii(int64_t arg0, int arg1, int _default) {
	#ifdef WASM
	return EM_ASM_INT({
		return window.ggpo_gml_wasm_exec($0, $1, $2);
		}, id, (double)arg0, arg1);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	args[2].setInt32(arg1);
	call(result, args);
	return result.getInt32(_default);
	#endif
}
int64_t gml_script_id::lll(int64_t arg0, int64_t arg1, int64_t _default) {
	#ifdef WASM
	return (int64_t)EM_ASM_DOUBLE({
		return window.ggpo_gml_wasm_exec($0, $1, $2);
		}, id, (double)arg0, (double)arg1);
	#else
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	args[2].setInt64(arg1);
	call(result, args);
	return result.getInt64(_default);
	#endif
}