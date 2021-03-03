#version 330

// input
in vec2 fragmentPosition;
in vec2 fragmentUV;
in vec4 fragmentColor;

// output
out vec4 color;

// uniform
uniform vec2 visionCenter;
uniform float visionRadius;

// texture uniform
uniform sampler2D asset;

void main() {
    vec4 textureColor = texture(asset, fragmentUV);

    // distance from center of circle to some point in world space
    float dist = length(fragmentPosition - visionCenter);

    // if another texture is closer than (visionRadius * 0.5f) units, than render it
    if(dist < visionRadius * 0.5f){
        float factor = dist / visionRadius;
        float intensity = pow(0.01f, factor) - 0.01f;
        color = fragmentColor * textureColor * intensity;
    }else{
        color = fragmentColor * textureColor * 0.0f;
    }

    
}