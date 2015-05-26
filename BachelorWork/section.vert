#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 mvp;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normalPoints;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 pos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 position;
uniform vec3 size;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	vec3 new_position = mvp;
	mat4 size_matrix = mat4(1);
	size_matrix[0][0] = size.x;
	size_matrix[1][1] = size.y;
	size_matrix[2][2] = size.z;
	mat4 pos_matrix = mat4(1);
	pos_matrix[0][3] = position.x;
	pos_matrix[1][3] = position.y;
	pos_matrix[2][3] = position.z;
	mat4 res = size_matrix*pos_matrix;
	gl_Position =  MVP * (vec4(mvp, 1)*res);
	pos = gl_Position;
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

