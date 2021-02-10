#version 330

// input
in vec2 fragmentPosition;
in vec4 fragmentColor;

// output
out vec4 color;

void main() {
    // float x = pow(fragmentPosition.x - 120.0f, 2);
    // float y = pow(fragmentPosition.y - 120.0f, 2);
    // float dist = sqrt(x + y);
    // float norm = dist / 120.0f;
    // float intensity = pow(0.01f, norm) - 0.01f;

    // normalized value [0;1]
    float x = length(fragmentPosition - vec2(120.0f, 120.0f)) / 120.0f; 

    // final intensity
    float intensity = pow(0.01f, x) - 0.01f;

    color = vec4(fragmentColor.rgb, fragmentColor.a * intensity * 1.2f);
}