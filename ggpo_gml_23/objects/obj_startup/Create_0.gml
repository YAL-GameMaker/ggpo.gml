host_dlg = -1;
global.__test_mode = undefined;
if (os_type != os_windows) {
	host_dlg = show_question_async("Host?");
} else {
	instance_create_layer(0, 0, layer, obj_test);
}