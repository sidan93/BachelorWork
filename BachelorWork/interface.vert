#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 mvp;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

void main()
{
	gl_Position = vec4(mvp, 1);
	UV = vertexUV;
}

