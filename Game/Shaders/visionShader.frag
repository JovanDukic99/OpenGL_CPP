#version 330

// input
in vec4 fragmentColor;
in vec2 fragmentPosition;

// output
out vec4 color;

// uniform
uniform float visionRadius;
uniform vec2 visionCenter;

void main() {
    float intensity = length(fragmentPosition - visionCenter) / visionRadius;

    color = fragmentColor * (1.0f - intensity);
}