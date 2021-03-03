#include "GLSL_Duplicate.h"

GLSL_Duplicate::GLSL_Duplicate(GLSL_Square square, Light* light1, Light* light2) : square(square), light1(light1), light2(light2) {

}

GLSL_Square GLSL_Duplicate::getGLSL_Square() const {
	return square;
}

Light* GLSL_Duplicate::getLight1() const {
	return light1;
}

Light* GLSL_Duplicate::getLight2() const {
	return light2;
}
