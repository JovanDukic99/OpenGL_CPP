#include "Utils.h"
#include "Config.h"

float normalize(float x, float y) {
	return ((x / y) * 2.0f) - 1.0f;
}

float denormalize(float z, float y) {
	return ((1.0f + z) * y) / 2.0f;
}
