#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 section;
in vec4 pos;

uniform sampler2D mainSampler;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main(){

	// Output color = color of the texture at the specified UV
	color = texture2D(mainSampler, UV);

	if (pos.x > section.x && pos.y > section.y && pos.z > section.z)
		discard;
}