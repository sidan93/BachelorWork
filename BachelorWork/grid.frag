#version 330 core

// Interpolated values from the vertex shaders
in vec4 section;
in vec4 pos;

uniform sampler2D mainSampler;
uniform float alpha;
uniform mat4 MVP;
uniform vec3 cameraPosition;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.

void main(){

	// Output color = color of the texture at the specified UV
	//color = normalize(normalize(vec4(mvp1,1)) - normalize(vec4(cameraPosition, 1)));
	//vec4 alphaBlend = normalize(pos - vec4(cameraPosition, 1));
	//color.a = sqrt(alphaBlend.x*alphaBlend.x + alphaBlend.y*alphaBlend.y + alphaBlend.z*alphaBlend.z);
	//color.a = 0.2;
	color = vec4(0.5,0,0,0.2);
	
	if (pos.x > section.x && pos.y > section.y && pos.z > section.z)
		discard;
}