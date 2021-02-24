#version 330

// input
in vec2 vertexPosition;
in vec4 vertexColor;

// uniform
uniform mat4 cameraMatrix;

// output
out vec4 fragmentColor;
out vec2 fragmentPosition;

void main() {
    gl_Position = cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f);

    fragmentColor = vertexColor;
    fragmentPosition = vertexPosition;
}