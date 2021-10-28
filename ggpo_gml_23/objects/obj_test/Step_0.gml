
ggpo_idle(10);
buffer_seek(local_input, buffer_seek_start, 0);
buffer_write(local_input, buffer_u8, 0
    | (keyboard_check(vk_left) << 0)
    | (keyboard_check(vk_right) << 1)
    | (keyboard_check(vk_up) << 2)
    | (keyboard_check(vk_down) << 3)
    | (keyboard_check_pressed(vk_space) << 4) // doing this wrong is a good way to force misprediction
);
if (ggpo_add_local_input(local_player, local_input, ggpo_input_size) == ggpo_ok) {
    scr_advance_frame();
}