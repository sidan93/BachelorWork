#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

out vec3 pos;
out vec3 fragmentColor;

out vec3 pos1;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	pos = position;
	gl_Position =  MVP * vec4(position, 1);
	
}
