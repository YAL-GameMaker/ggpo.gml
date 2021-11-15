if (global.websocket_enabled) {
    ggpo_websocket_async_network();
} else {
    ggpo_default_async_network();
}