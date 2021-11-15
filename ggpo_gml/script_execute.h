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

class CInstanceBase {
public:
	GMLVar* yyvars;
	virtual ~CInstanceBase() {};
	virtual GMLVar& InternalGetYYVarRef(int index) = 0;
	virtual GMLVar& InternalGetYYVarRefL(int index) = 0;
};
class YYObjectBase : public CInstanceBase {
public:
	virtual ~YYObjectBase() {};
	virtual bool Mark4GC(uint32* _pM, int _numObjects) { return false; }
	virtual bool MarkThisOnly4GC(uint32* _pM, int _numObjects) { return false; }
	virtual bool MarkOnlyChildren4GC(uint32* _pM, int _numObjects) { return false; }
	virtual void Free() {}
	virtual void ThreadFree(void* _pGCContext) {}
	virtual void PreFree() {}

	YYObjectBase* m_pNextObject;
	YYObjectBase* m_pPrevObject;
	YYObjectBase* m_pPrototype;
	void* m_pcre;
	void* m_pcreExtra;
	const char* m_class;
	void* m_getOwnProperty;
	void* m_deleteProperty;
	void* m_defineOwnProperty;
	void* m_yyvarsMap;
	void** m_pWeakRefs;
	uint32 m_numWeakRefs;
	uint32 m_nvars;
	uint32 m_flags;
	uint32 m_capacity;
	uint32 m_visited;
	uint32 m_visitedGC;
	int32 m_GCgen;
	int32 m_GCcreationFrame;
	int m_slot;
	int m_kind;
	int m_rvalueInitType;
	int m_curSlot;
};
class GMLClosure : public YYObjectBase {
public:
	void* m_callScript;
	GMLFunc* m_cppFunc;
	void* m_yycFunc;
};

namespace script_execute {
	extern GMLClosure* self;
	extern GMLFunc* raw;
	void call(GMLVar& result, GMLVar* args, size_t argc);
	template<size_t argc> void call(GMLVar& result, GMLVar(&args)[argc]) {
		call(result, args, argc);
	}
}
// helpers are named based on arguments+return type, one char per argument and last for return
// i=int, l=int64
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
	//int64_t l(int64_t _default = 0);

	int ii(int arg0, int _default = 0);
	int li(int64_t arg0, int _default = 0);
	int64_t ll(int64_t arg0, int64_t _default = 0);

	int lii(int64_t arg0, int arg1, int _default = 0);
	int64_t lll(int64_t arg0, int64_t arg1, int64_t _default = 0);
};