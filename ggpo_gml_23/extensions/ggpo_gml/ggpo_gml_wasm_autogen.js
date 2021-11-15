function ggpo_gml_wasm_autowrap() {
	window._ggpo_do_game_state_save_3_raw = (function() {
		var wfn = Module._ggpo_do_game_state_save_3_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_idle_raw = (function() {
		var wfn = Module._ggpo_idle_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_advance_frame_raw = (function() {
		var wfn = Module._ggpo_advance_frame_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_player_is_active_raw = (function() {
		var wfn = Module._ggpo_player_is_active_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_set_input_size_raw = (function() {
		var wfn = Module._ggpo_set_input_size_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_start_session_raw = (function() {
		var wfn = Module._ggpo_start_session_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_start_spectating_raw = (function() {
		var wfn = Module._ggpo_start_spectating_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size, arg$_arg_host_ip) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var ex$_arg_host_ip = allocateUTF8(arg$_arg_host_ip);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size, ex$_arg_host_ip);
			ggpo_gml_wasm_free(ex$_in_ptr);
			_free(ex$_arg_host_ip)
			return result;
		}
	})();
	window._ggpo_start_synctest_raw = (function() {
		var wfn = Module._ggpo_start_synctest_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_close_session_raw = (function() {
		var wfn = Module._ggpo_close_session_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_add_local_player_raw = (function() {
		var wfn = Module._ggpo_add_local_player_raw;
		return function(arg$_inout_ptr, arg$_inout_ptr_size) {
			var ex$_inout_ptr = ggpo_gml_wasm_alloc(arg$_inout_ptr_size, arg$_inout_ptr);
			var result = wfn(ex$_inout_ptr, arg$_inout_ptr_size);
			ggpo_gml_wasm_free(ex$_inout_ptr, arg$_inout_ptr, arg$_inout_ptr_size);
			return result;
		}
	})();
	window._ggpo_add_remote_player_raw = (function() {
		var wfn = Module._ggpo_add_remote_player_raw;
		return function(arg$_inout_ptr, arg$_inout_ptr_size, arg$_arg_ip) {
			var ex$_inout_ptr = ggpo_gml_wasm_alloc(arg$_inout_ptr_size, arg$_inout_ptr);
			var ex$_arg_ip = allocateUTF8(arg$_arg_ip);
			var result = wfn(ex$_inout_ptr, arg$_inout_ptr_size, ex$_arg_ip);
			ggpo_gml_wasm_free(ex$_inout_ptr, arg$_inout_ptr, arg$_inout_ptr_size);
			_free(ex$_arg_ip)
			return result;
		}
	})();
	window._ggpo_disconnect_player_raw = (function() {
		var wfn = Module._ggpo_disconnect_player_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_set_frame_delay_raw = (function() {
		var wfn = Module._ggpo_set_frame_delay_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_add_local_input_raw = (function() {
		var wfn = Module._ggpo_add_local_input_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_synchronize_input_raw = (function() {
		var wfn = Module._ggpo_synchronize_input_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_preinit_2_raw = (function() {
		var wfn = Module._ggpo_preinit_2_raw;
		return function(arg$_in_ptr, arg$_in_ptr_size) {
			var ex$_in_ptr = ggpo_gml_wasm_alloc(arg$_in_ptr_size, arg$_in_ptr);
			var result = wfn(ex$_in_ptr, arg$_in_ptr_size);
			ggpo_gml_wasm_free(ex$_in_ptr);
			return result;
		}
	})();
	window._ggpo_do_network_send_packet_2 = (function() {
		var wfn = Module._ggpo_do_network_send_packet_2;
		return function(arg$out_buffer, arg$out_buffer_len) {
			var ex$out_buffer = ggpo_gml_wasm_alloc(arg$out_buffer_len);
			var result = wfn(ex$out_buffer, arg$out_buffer_len);
			ggpo_gml_wasm_free(ex$out_buffer, arg$out_buffer, arg$out_buffer_len);
			return result;
		}
	})();
	window._ggpo_preinit_1 = (function() {
		var wfn = Module._ggpo_preinit_1;
		return function(arg$_script_execute, arg$_script_execute_size_dummy) {
			var ex$_script_execute = ggpo_gml_wasm_alloc(arg$_script_execute_size_dummy, arg$_script_execute);
			var result = wfn(ex$_script_execute, arg$_script_execute_size_dummy);
			ggpo_gml_wasm_free(ex$_script_execute);
			return result;
		}
	})();
	window._ggpo_set_game_name = (function() {
		var wfn = Module._ggpo_set_game_name;
		return function(arg$name) {
			var ex$name = allocateUTF8(arg$name);
			var result = wfn(ex$name);
			_free(ex$name)
			return result;
		}
	})();
}