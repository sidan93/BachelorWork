#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

in vec4 pos;
uniform sampler2D mainSampler;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main(){

	// Output color = color of the texture at the specified UV
	//color.g *= 2;
	//color = normalize(vec3(pos.x, pos.y, pos.z));
	color.r = 0.4;
	color.a = 0.3;
}