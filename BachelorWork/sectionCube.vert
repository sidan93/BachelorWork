#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 mvp;
layout(location = 1) in vec3 colorCube;

out vec3 pos;
out vec3 fragmentColor;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	pos = mvp;
	fragmentColor = colorCube;
	gl_Position =  MVP * vec4(mvp, 1);
}

