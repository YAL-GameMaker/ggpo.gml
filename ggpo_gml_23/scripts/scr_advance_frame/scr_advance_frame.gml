/// @self {obj_test}
function scr_advance_frame() {
    if (ggpo_synchronize_input(inputs) != ggpo_ok) exit;
    var _buf = inputs;
    with (obj_player) {
        var _offset = index * ggpo_input_size;
        var _keys = buffer_peek(_buf, _offset, buffer_u8)
        step(
            (_keys & (1 << 0)) != 0,
            (_keys & (1 << 1)) != 0,
            (_keys & (1 << 2)) != 0,
            (_keys & (1 << 3)) != 0,
            (_keys & (1 << 4)) != 0,
        );
    }
    ggpo_advance_frame();
}