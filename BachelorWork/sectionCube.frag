#version 330 core

// Ouput data
out vec4 color;

in vec3 pos;
in vec4 centerCubeOut;

// Values that stay constant for the whole mesh.

void main()
{
	vec3 center = vec3(centerCubeOut.x, centerCubeOut.y, centerCubeOut.z);
	// Алгоритм с расчетом по кажой стороне
	color = vec4(
		vec3(
			abs(distance(pos, center))/(int(centerCubeOut.w) % 1000), 
			abs(distance(pos, center))/(int(centerCubeOut.w / 1000) % 1000), 
			abs(distance(pos, center))/(int(centerCubeOut.w / 1000 / 1000))
		), 1);
	// Алгоритм со средней длинной
	//color = vec4(vec3(distance(pos, center)/centerCubeOut.w, distance(pos, center)/centerCubeOut.w, distance(pos, center))/centerCubeOut.w, 1);
}