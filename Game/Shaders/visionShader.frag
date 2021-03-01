#version 330

// input
in vec4 fragmentColor;
in vec2 fragmentPosition;

// output
out vec4 color;

// uniform
// uniform float visionRadius;
// uniform vec2 visionCenter;

void main() {
    // float factor = length(fragmentPosition - visionCenter) / visionRadius;
    // float intensity = pow(0.01f, factor) - 0.01f;
    // color = fragmentColor * intensity;
    color = fragmentColor;
}