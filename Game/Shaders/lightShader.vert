#version 330

// input
in vec2 vertexPosition;
in vec4 vertexColor;

// uniform
uniform mat4 cameraMatrix;

// output
out vec4 fragmentPosition;
out vec4 fragmentColor;

void main() {
    gl_Position = cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f);

    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
}