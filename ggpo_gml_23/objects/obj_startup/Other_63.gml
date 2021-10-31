if (async_load[?"id"] == host_dlg) {
	host_dlg = -1;
	global.__test_mode = !async_load[?"status"];
	instance_create_layer(0, 0, layer, obj_test);
}