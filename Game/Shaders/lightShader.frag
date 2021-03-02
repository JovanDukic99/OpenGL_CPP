#version 330

// input
in vec2 fragmentPosition;
in vec4 fragmentColor;

// output
out vec4 color;

// uniform
uniform vec2 lightSource;
uniform float lightRadius;

void main() {
    float factor = length(fragmentPosition - lightSource) / lightRadius;

    float intensity = pow(0.01f, factor) - 0.01f;
    color = fragmentColor * intensity;

    // if(factor > 1.0f){
    //     color = vec4(fragmentColor.rgb, 0.0f);
    // }else{
    //     color = vec4(fragmentColor.rgb, fragmentColor.a);
    // }

    // color = fragmentColor;
}