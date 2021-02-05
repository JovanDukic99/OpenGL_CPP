#version 330

// input
in vec2 vertexPosition;
in vec4 vertexColor;

// output
out vec4 fragmentColor;

void main() {
    gl_Position.xy = vertexPosition;

    gl_Position.z = 0.0f;

    gl_Position.w = 1.0f;

    fragmentColor = vertexColor;
}