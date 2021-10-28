#include "script_execute.h"

namespace script_execute {
	GMLClosure* self;
	GMLFunc* raw;
	void call(GMLVar& result, GMLVar* args, size_t argc) {
		raw(result, self, self, argc, args);
	}
}

int gml_script_id::i(int _default) {
	static GMLVar result = 0;
	static GMLVar args[] = { 0 };
	args[0].setInt32(id);
	call(result, args);
	return result.getInt32(_default);
}
int gml_script_id::ii(int arg0, int _default) {
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0 };
	args[0].setInt32(id);
	args[1].setInt32(arg0);
	call(result, args);
	return result.getInt32(_default);
}
int gml_script_id::li(int64_t arg0, int _default) {
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	call(result, args);
	return result.getInt32(_default);
}
int gml_script_id::lii(int64_t arg0, int arg1, int _default) {
	static GMLVar result = 0;
	static GMLVar args[] = { 0, 0, 0 };
	args[0].setInt32(id);
	args[1].setInt64(arg0);
	args[2].setInt32(arg1);
	call(result, args);
	return result.getInt32(_default);
}