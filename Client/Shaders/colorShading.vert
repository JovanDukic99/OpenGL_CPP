#version 330

// the vertex shader operates on each vertex

// input data (in) from the VBO
// Each vertex contains of 2 floats (x, y)
// every in... has an index, it counts from 0
// that index we use in our program to fill inputs

in vec2 vertexPosition;
in vec2 vertexUV;
in vec4 vertexColor;

// flat for no interpolation
// ignors color of some vertices
// must be set on same variable in vertex and fragment shader
/* flat out vec4 fragmentColor; */

// output data (out) to fragment shader
// smooth means linear interpolation
out vec2 fragmentPosition;
out vec2 fragmentUV;
smooth out vec4 fragmentColor;

// uniform vec2 offset;
uniform mat4 cameraMatrix;

void main() { 
    // set the x,y coordinates of vertex

    // float x = (cos(time) - 1) * 0.5f;
    // float y = (sin(time) - 1) * 0.5f;

    gl_Position = cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f);

    // z coordinate is 0, bcs we are in 2D space
    // gl_Position.z = 0.0f;

    // indicate that the coordinates are normalized
    // gl_Position.w = 1.0f;

    // setting up fragment position
    fragmentPosition = vertexPosition;

    // setting up fragment color
    fragmentColor = vertexColor;

    // setting up fragmentUV
    fragmentUV = vec2(vertexUV.x, 1.0f - vertexUV.y);
}

