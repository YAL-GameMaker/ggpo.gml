#pragma once
#include "gml_ext.h"

enum class GMLVarType : int32_t {
	Real = 0,
	String = 1,
	Array = 2,
	Pointer = 3,
	Undefined = 5,
	Int32 = 7,
	Int64 = 10,
	Bool = 13,
};

struct GMLVar {
	union {
		int32_t vInt32;
		int64_t vInt64;
		double vReal;
		const void* vPtr;
	};
	int32_t flags;
	GMLVarType type;
	GMLVar() {
		vReal = 0;
		flags = 0;
		type = GMLVarType::Real;
	}
	GMLVar(double val) {
		vReal = val;
		flags = 0;
		type = GMLVarType::Real;
	}

	void setReal(double v) {
		type = GMLVarType::Real;
		vReal = v;
	}
	double getReal(double _default = 0) {
		switch (type) {
		case GMLVarType::Real:
			return vReal;
		case GMLVarType::Int32:
			return vInt32;
		case GMLVarType::Int64:
			return (double)vInt64;
		default:
			return _default;
		}
	}

	void setInt32(int32_t val) {
		type = GMLVarType::Int32;
		vInt32 = val;
	}
	int32_t getInt32(int32_t _default = 0) {
		switch (type) {
		case GMLVarType::Real:
			return (int32_t)vReal;
		case GMLVarType::Int32:
			return vInt32;
		case GMLVarType::Int64:
			return (int32_t)vInt64;
		default:
			return _default;
		}
	}

	void setInt64(int64_t val) {
		type = GMLVarType::Int64;
		vInt64 = val;
	}
	int64_t getInt64(int64_t _default = 0) {
		switch (type) {
		case GMLVarType::Real:
			return (int64_t)vReal;
		case GMLVarType::Int32:
			return vInt32;
		case GMLVarType::Int64:
			return vInt64;
		default:
			return _default;
		}
	}
};
typedef void(GMLFunc)(GMLVar& result, void* self, void* other, int argc, GMLVar* argv);

struct GMLClosure {
	int __unknown[26];
	GMLFunc* func;
};

/// helpers are named based on arguments+return type, one 
namespace script_execute {
	extern GMLClosure* self;
	extern GMLFunc* raw;
	void call(GMLVar& result, GMLVar* args, size_t argc);
	template<size_t argc> void call(GMLVar& result, GMLVar(&args)[argc]) {
		call(result, args, argc);
	}
}
struct gml_script_id {
	int id;
	gml_script_id() : id(-1) { }
	gml_script_id(int _id) : id(_id) { }
	gml_script_id(const int& _id) : id(_id) { }
	void operator = (const int _id) { id = _id; }

	template<size_t argc> inline void call(GMLVar& result, GMLVar(&args)[argc]) {
		script_execute::call(result, args);
	}

	int i(int _default = 0);
	int ii(int arg0, int _default = 0);
	int li(int64_t arg0, int _default = 0);
	int lii(int64_t arg0, int arg1, int _default = 0);
};