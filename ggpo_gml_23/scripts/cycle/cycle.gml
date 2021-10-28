/// @description  cycle(value, min, max)
/// @param value
/// @param  min
/// @param  max
function cycle(argument0, argument1, argument2) {
	var offset = argument1;
	var value = argument0 - offset;
	var range = argument2 - offset;
	value = value mod range;
	if (value < 0) value += range;
	return value + offset;
}
