#version 330

// input
in vec2 fragmentUV;
in vec4 fragmentColor;

// output
out vec4 color;

// uniform
uniform sampler2D asset;

void main() {
    vec4 textureColor = texture(asset, fragmentUV);
    color = fragmentColor * textureColor;
}