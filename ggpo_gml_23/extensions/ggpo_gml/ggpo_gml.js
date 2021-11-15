var ggpo_gml_was_ready = false;
var Module = {
	preRun: [],
	postRun: [],
	print: function(text) {
		console.log("[WASM]", text);
	},
	printErr: function(text) {
		if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
		console.error(text);
	},
	canvas: (function() {
		var canvas = document.getElementById('canvas');		
		return canvas;
	})(),
	setStatus: function(text) {
		console.log("[WASM Status]", text);
	},
	totalDependencies: 0,
	remainingDependencies: 1,
	monitorRunDependencies: function(left) {
		this.remainingDependencies = left;
		this.totalDependencies = Math.max(this.totalDependencies, left);
	},
	onRuntimeInitialized: function() {
		ggpo_gml_was_ready = true;
		console.log("GGPO has loaded!");
		ggpo_gml_wasm_autowrap();
		window.gml_Script_gmcallback_ggpo_preinit();
	}
};

(function() {
	var _script = document.createElement("script");
	_script.addEventListener("load", function(e) {
		console.log("ggpo_gml_wasm.js loaded");
	});
	_script.src = "html5game/ggpo_gml_wasm.js";
	document.body.appendChild(_script);
})();

function ggpo_gml_is_ready() {
	return ggpo_gml_was_ready;
}
function ggpo_gml_wasm_alloc(size, in_abuf) {
	var wptr = Module._malloc(size);
	if (in_abuf) {
		var u8a = new Uint8Array(in_abuf);
		var u8m = Module.HEAPU8;
		for (var i = 0; i < size; i++) u8m[wptr + i] = u8a[i];
	}
	return wptr;
}
function ggpo_gml_wasm_free(wptr, out_abuf, out_size) {
	if (out_abuf) {
		var u8a = new Uint8Array(out_abuf);
		var u8m = Module.HEAPU8;
		for (var i = 0; i < out_size; i++) u8a[i] = u8m[wptr + i];
	}
	Module._free(wptr);
}

var ggpo_gml_wasm_fixed_arraybuf;
var ggpo_gml_wasm_fixed_size;
var ggpo_gml_wasm_fixed_u8array;
var ggpo_gml_wasm_fixed_wptr;
function ggpo_gml_wasm_init_fixed_buffer(abuf, size) {
	ggpo_gml_wasm_fixed_size = size;
	ggpo_gml_wasm_fixed_buffer = abuf;
	ggpo_gml_wasm_fixed_u8array = new Uint8Array(abuf);
	ggpo_gml_wasm_fixed_wptr = Module._malloc(size);
	Module._ggpo_gml_fixed_buffer_set_wptr(ggpo_gml_wasm_fixed_wptr);
}
function ggpo_gml_wasm_get_fixed_buffer() {
	var u8a = ggpo_gml_wasm_fixed_u8array;
	var u8m = Module.HEAPU8;
	var wptr = ggpo_gml_wasm_fixed_wptr;
	var size = ggpo_gml_wasm_fixed_size;
	for (var i = 0; i < size; i++) u8a[i] = u8m[wptr + i];
}
function ggpo_gml_wasm_set_fixed_buffer() {
	var u8a = ggpo_gml_wasm_fixed_u8array;
	var u8m = Module.HEAPU8;
	var wptr = ggpo_gml_wasm_fixed_wptr;
	var size = ggpo_gml_wasm_fixed_size;
	for (var i = 0; i < size; i++) u8m[wptr + i] = u8a[i];
}

function ggpo_gml_wasm_exec_init(fn) {
	window.ggpo_gml_wasm_exec = function(_0, _1, _2, _3, _4, _5, _6, _7) {
		//console.log("wasm_exec", _0, _1, _2, _3, _4, _5, _6, _7);
		return window.gml_Script_gmcallback_ggpo_gml_script_execute(fn, fn, _0, _1, _2, _3, _4, _5, _6, _7);
	}
}