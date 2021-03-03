#version 330

// input
in vec4 fragmentColor;
in vec2 fragmentPosition;

// output
out vec4 color;

// uniform
uniform float visionRadius;
uniform float intensity;
uniform vec2 visionCenter;

void main() {
    float dist = length(fragmentPosition - visionCenter) / visionRadius;
    float factor = pow(0.01f, dist) - 0.01f;
    color = fragmentColor * factor * intensity;
}