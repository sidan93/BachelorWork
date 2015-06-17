#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

uniform sampler2D mainSampler;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main()
{
	color = texture2D(mainSampler, UV);
	if (color.r >= 1 && color.g >= 1 && color.b >= 1)
		discard;
}