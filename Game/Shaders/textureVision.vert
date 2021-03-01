#version 330

// input
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

// uniform
uniform mat4 cameraMatrix;

// output
out vec2 fragmentPosition;
out vec2 fragmentUV;
out vec4 fragmentColor;

void main() {
    gl_Position = cameraMatrix * vec4(vertexPosition, 0.0f, 1.0f);

    fragmentPosition = vertexPosition;
    fragmentUV = vec2(vertexUV.x, 1.0f - vertexUV.y);
    fragmentColor = vertexColor;
}