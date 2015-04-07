#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 mvp;

// Output data ; will be interpolated for each fragment.
out vec4 pos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	vec3 new_position = mvp;
	gl_Position =  MVP * vec4(mvp, 1);
	pos = gl_Position;
}

