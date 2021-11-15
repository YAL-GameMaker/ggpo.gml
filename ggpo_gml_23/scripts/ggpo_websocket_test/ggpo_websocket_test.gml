global.websocket_enabled = false;
global.websocket_debug = true;
global.websocket_remote_ip = "";
global.websocket_remote_port = 0;
function ggpo_websocket_test() {
    global.websocket_enabled = true;
    global.websocket_server = -1; // native: listener, web: N/A
    global.websocket_client = -1; // native: connected web client, web: ourselves
    global.websocket_connected = false; // native: N/A, web: ready to send
    ggpo_on_network_create_socket = function(_port, _retries) {
        if (ggpo_gml_is_js) {
            global.websocket_client = -1;
        } else {
            global.websocket_server = network_create_server(network_socket_ws, _port, 1);
            if (global.websocket_debug) show_debug_message("Created a WebSocket server at port " + string(_port) + ".");
        }
        return 1;
    }
    ggpo_on_network_destroy_socket = function(_skt) {
        if (global.websocket_client != -1) {
            network_destroy(global.websocket_client);
            global.websocket_client = -1;
        }
        if (global.websocket_server != -1) {
            network_destroy(global.websocket_server);
            global.websocket_server = -1;
        }
        global.websocket_connected = false;
    }
    ggpo_on_network_send_packet = function(_socket, _url, _port, _buf, _len) {
        global.websocket_remote_ip = _url;
        global.websocket_remote_port = _port;
        if (ggpo_gml_is_js) {
            if (global.websocket_client == -1) {
                if (global.websocket_debug) show_debug_message("Connecting to " + string(_url) + ":" + string(_port) + "...");
                global.websocket_client = network_create_socket(network_socket_ws);
                global.__ggpo_default_packet_queue[?global.websocket_client] = ds_queue_create();
                network_connect_async(global.websocket_client, _url, _port);
            }
            if (!global.websocket_connected) return 0;
            return network_send_packet(global.websocket_client, _buf, _len);
        } else {
            if (global.websocket_client == -1) return 0;
            return network_send_packet(global.websocket_client, _buf, _len);
        }
    }
    ggpo_on_network_receive_packet = function(_socket) {
        return ggpo_default_network_receive_packet(global.websocket_client);
    }
}
function ggpo_websocket_async_network() {
    if (!global.websocket_enabled) return false;
    var _e/*:async_load_network*/ = /*#cast*/ async_load;
    switch (_e[?"type"]) {
        case network_type_non_blocking_connect:
            if (!ggpo_gml_is_js) exit;
            global.websocket_connected = true;
            show_debug_message("Connected!");
            break;
        case network_type_connect:
            if (ggpo_gml_is_js) exit;
            if (global.websocket_client == -1) {
                global.websocket_client = _e[?"socket"];
                global.__ggpo_default_packet_queue[?global.websocket_client] = ds_queue_create();
                show_debug_message("Client connected!");
            }
            break;
        case network_type_data:
            _e[?"ip"] = global.websocket_remote_ip;
            _e[?"port"] = global.websocket_remote_port;
            ggpo_default_async_network();
            break;
    }
    return true;
}