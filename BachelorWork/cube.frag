#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 section;
in vec4 pos;

uniform sampler2D mainSampler;
uniform int sectionIsEnable;
uniform float alpha;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main(){

	// Output color = color of the texture at the specified UV
	color = texture2D(mainSampler, UV);
	color.a = alpha;
	
	if (sectionIsEnable == 1)
		if (pos.x > section.x - 1 && pos.y > section.y - 1 && pos.z > section.z - 1)
			discard;
}