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
uniform float intensity;

// texture uniform
uniform sampler2D asset;

void main() {
    vec4 textureColor = texture(asset, fragmentUV);

    float dist = length(fragmentPosition - visionCenter) / visionRadius;
    float factor = pow(0.01f, dist) - 0.01f;
    color = fragmentColor * textureColor * factor * intensity;
    color = fragmentColor * textureColor;

    // if another texture is closer than (visionRadius * 0.5f) units, than render it
    // if(dist < visionRadius * 0.5f){
       
    // }else{
    //     color = fragmentColor * textureColor * 0.0f;
    // }

    
}