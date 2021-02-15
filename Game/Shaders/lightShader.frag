#version 330

// input
in vec4 fragmentPosition;
in vec4 fragmentColor;

// output
out vec4 color;

void main() {

    vec2 vector = 120.0f - fragmentPosition;
    float factor = length(vector) / intensity;

    color = vec4(fragmentColor.rgb, fragmentColor.a * (1.0f - factor));
}