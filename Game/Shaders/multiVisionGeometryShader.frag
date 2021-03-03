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

void main() {
    float factor1 = length(fragmentPosition - visionCenter1) / visionRadius1;
    float factor2 = length(fragmentPosition - visionCenter2) / visionRadius2;
    
    float intensity1 = pow(0.01f, factor1) - 0.01f;
    float intensity2 = pow(0.01f, factor2) - 0.01f;

    float intensity = intensity1 + intensity2;

    intensity = clamp(intensity, 0.0f, 1.0f);
    
    color = fragmentColor * intensity;
}