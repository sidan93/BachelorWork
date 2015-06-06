#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 mvp;

// Output data ; will be interpolated for each fragment.
out vec4 pos;
out vec4 section;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 sectionStart;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	pos = vec4(mvp, 1);
	gl_Position =  MVP * pos;

	// Высчитываем сечение
	section = vec4(sectionStart, 1);
}

