#version 330

// the fragment shader operates on each pixel in a given polygon

// receiving fragmentColor variable form vertex shader
// flat for no interpolation
// ignors color of some vertices
// must be set on same variable in vertex and fragment shader
/* flat */ smooth in vec4 fragmentColor;

in vec2 fragmentPosition;
in vec2 fragmentUV;

// this is the 3 component float vector that gets outputted to the screen for each pixel
out vec4 color;

// uniform variable, unique variable for an entire mesh
// send just one variable for all vertices unlike copies
// like fragmentColor 
// uniform float time;
// uniform float offsetY;

// sampler2D is 2D texture
uniform sampler2D asset;

void main() {

	// texture
	vec4 textureColor = texture(asset, fragmentUV);

	// setting up the color to red, hardcored
	// color = vec3(1.0, 0.0, 1.0, 1.0);	

	// setting up color to reveived color value
	// (1 + cos(x)) - y:[0,2]
	// (1 + cos(x)) * 0.5 - y:[0,1]
	// because rgba ranges from [0,1]
	// color = vec4(fragmentColor.r * (1 + cos((fragmentPosition.x) + time)) * 0.5,
	// 			 fragmentColor.g * (1 + cos((fragmentPosition.y * 4.0) + time)) * 0.5,
	// 			 fragmentColor.b * (1 + cos((fragmentPosition.x * 2) + time)) * 0.5,
	// 			 fragmentColor.a);

    // gl_FragCoord.y and gl_FragCoord.x are window coordinates
	// float loopTime = mod(time, 5.0f);
	// float lerpValue = loopTime / 5.0f;
    // float lerpValue = (gl_FragCoord.y - offsetY) / 360.0f;
    
    // color = mix(vec4(0.0f, 0.0f, 1.0f, 1.0f),
    //     vec4(1.0f, 0.0f, 0.0f, 1.0f), lerpValue) * textureColor;

	color = fragmentColor * textureColor;
}
