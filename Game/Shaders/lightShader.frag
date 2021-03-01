#version 330

// input
in vec2 fragmentUV;
in vec4 fragmentColor;

// output
out vec4 color;

void main() {
    float factor = length(fragmentUV);

    float intensity = pow(0.01f, factor) - 0.01f;
    color = vec4(fragmentColor.rgb, fragmentColor.a * intensity);

    if(factor > 1.0f){
        color = vec4(fragmentColor.rgb, 0.0f);
    }else{
        color = vec4(fragmentColor.rgb, fragmentColor.a);
    }

    color = fragmentColor;
}