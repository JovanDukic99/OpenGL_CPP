#version 330

// input
in vec2 vertexPosition;
in vec4 vertexColor;

// output
out vec2 fragmentPosition;
out vec4 fragmentColor;

// uniform
uniform mat4 cameraMatrix;

void main() {
    gl_Position = cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f);

    fragmentColor = vertexColor;
    fragmentPosition = vertexPosition;
}