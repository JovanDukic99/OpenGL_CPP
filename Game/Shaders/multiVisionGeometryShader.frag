#version 330

// input
in vec4 fragmentColor;
in vec2 fragmentPosition;

// output
out vec4 color;

// uniform
uniform float visionRadius1;
uniform vec2 visionCenter1;

uniform float visionRadius2; 
uniform vec2 visionCenter2;

uniform float intensity1;
uniform float intensity2;

void main() {
    float dist1 = length(fragmentPosition - visionCenter1) / visionRadius1;
    float dist2 = length(fragmentPosition - visionCenter2) / visionRadius2;
    
    float factor1 = pow(0.01f, dist1) - 0.01f;
    float factor2 = pow(0.01f, dist2) - 0.01f;

    float factor = factor1 + factor2;
    float intensity = (intensity1 + intensity2) * 0.5f;

    factor = clamp(factor, 0.0f, 1.0f);
    
    color = fragmentColor * factor * intensity;
}