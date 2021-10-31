var _fork = global.__test_mode
if (_fork == undefined) _fork = parameter_string(parameter_count() - 1) == "-fork";

global.__ggpo_default_verbose = true;
window_set_caption("ggpo " + (_fork ? "client" : "server"))
//show_message("?" + string(_fork));
#macro ggpo_input_size 8
ggpo_set_input_size(ggpo_input_size);

local_input = buffer_create(ggpo_input_size, buffer_fixed, 1);
inputs = buffer_create(ggpo_input_size * 2, buffer_fixed, 1);
local_player = -1;
remote_player = -1;

if 0 ggpo_on_game_begin = function() {
    // OK!
}
ggpo_on_game_state_save = function(_buf, _frame) {
    var _pc = 0, _pc_at = buffer_tell(_buf);
    buffer_write(_buf, buffer_s32, 0);
    with (obj_player) {
        buffer_write(_buf, buffer_s32, index);
        save(_buf);
        _pc++;
    }
    buffer_poke(_buf, _pc_at, buffer_s32, _pc);
}
ggpo_on_game_state_load = function(_buf, _len) {
    var _pc = buffer_read(_buf, buffer_s32);
    repeat (_pc) {
        var _ind = buffer_read(_buf, buffer_s32);
        with (obj_player) if (index == _ind) {
            load(_buf);
            break;
        }
    }
}
ggpo_on_advance_frame = function() {
    scr_advance_frame();
}
if (_fork) {
    ggpo_start_session(2, 5394);
    local_player = ggpo_add_local_player(1);
    remote_player = ggpo_add_remote_player(2, "127.0.0.1", 5395);
} else {
    ggpo_start_session(2, 5395);
    remote_player = ggpo_add_remote_player(1, "127.0.0.1", 5394);
    local_player = ggpo_add_local_player(2);
}
for (var i = 0; i < 2; i++) {
    with (instance_create_depth(
        room_width * (0.25 + i * 0.5),
        room_height / 2,
        0,
        obj_player
    )) {
        index = i;
        image_blend = i ? c_red : c_blue;
    }
}
trace("local:", local_player, "remote:", remote_player);