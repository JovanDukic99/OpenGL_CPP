#version 330

// input
in vec4 fragmentColor;
in vec2 fragmentPosition;

// output
out vec4 color;

// uniform
uniform float visionRadius;
uniform vec2 visionCenter;

void main() {
    float factor = length(fragmentPosition - visionCenter) / visionRadius;

    if(factor < 1){
        color = fragmentColor;
    }else{
        color = fragmentColor * 0.5f;
    }
}