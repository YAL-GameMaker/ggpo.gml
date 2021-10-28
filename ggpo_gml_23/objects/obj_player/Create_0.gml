index = -1;
velx = 0;
vely = 0;
step = function(_left, _right, _forward, _backward, _warp) {
    if (_left) image_angle += 5;
    if (_right) image_angle -= 5;
    if (_forward ^^ _backward) {
        var _acc = (_forward - _backward) * 0.1
        velx += lengthdir_x(_acc, image_angle);
        vely += lengthdir_y(_acc, image_angle);
    } else {
        var _len = point_distance(0, 0, velx, vely);
        if (_len > 0) {
            _len = max(_len - 0.05, 0) / _len;
            velx *= _len;
            vely *= _len;
        }
    }
    if (_warp) {
        var _dist = 80;
        x += lengthdir_x(_dist, image_angle);
        y += lengthdir_y(_dist, image_angle);
    }
    x = cycle(x + velx, 0, room_width);
    y = cycle(y + vely, 0, room_height);
}
save = function(_buf) {
    buffer_write(_buf, buffer_f32, x);
    buffer_write(_buf, buffer_f32, y);
    buffer_write(_buf, buffer_f32, image_angle);
    buffer_write(_buf, buffer_f64, velx);
    buffer_write(_buf, buffer_f64, vely);
}
load = function(_buf) {
    x = buffer_read(_buf, buffer_f32);
    y = buffer_read(_buf, buffer_f32);
    image_angle = buffer_read(_buf, buffer_f32);
    velx = buffer_read(_buf, buffer_f64);
    vely = buffer_read(_buf, buffer_f64);
}
