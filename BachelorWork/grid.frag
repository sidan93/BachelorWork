#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 pos;
in vec3 mvp1;

uniform sampler2D mainSampler;
uniform float alpha;
uniform mat4 MVP;
uniform vec3 cameraPosition;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main(){

	// Output color = color of the texture at the specified UV
	color = normalize(normalize(vec4(mvp1,1)) - normalize(vec4(cameraPosition, 1)));

	vec4 alphaBlend = normalize(pos - vec4(cameraPosition, 1));
	//color.a = sqrt(alphaBlend.x*alphaBlend.x + alphaBlend.y*alphaBlend.y + alphaBlend.z*alphaBlend.z);
	color.a = 0.2;
}