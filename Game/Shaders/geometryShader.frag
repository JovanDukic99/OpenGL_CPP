#version 330

// input
in vec4 fragmentColor;

// output
out vec4 color;

// uniform
uniform float alpha;

void main() {
    color = vec4(fragmentColor.rgb, fragmentColor.a * alpha);
}