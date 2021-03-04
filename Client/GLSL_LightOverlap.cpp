#include "GLSL_LightOverlap.h"

GLSL_LightOverlap::GLSL_LightOverlap(GLSL_Square square, Light* light1, Light* light2) : square(square), light1(light1), light2(light2) {

}

GLSL_Square GLSL_LightOverlap::getGLSL_Square() const {
	return square;
}

Light* GLSL_LightOverlap::getLight1() const {
	return light1;
}

Light* GLSL_LightOverlap::getLight2() const {
	return light2;
}
