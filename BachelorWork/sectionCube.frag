#version 330 core

// Ouput data
out vec4 color;

in vec3 pos;
in vec3 fragmentColor;


// Values that stay constant for the whole mesh.
uniform vec3 sphereCenter;
uniform float sphereRadius;
uniform int sphereColoringCount;
uniform float sphereColoring[ 100 ];

float calcPower() {
	float MATH_PI = 3.1415926535897932;
	
	float efi = 0;
	float Mu = 4 * MATH_PI;
	float GenRadius = sphereRadius;
	int GenRadSplit = 100;
	float ResDist = distance(pos, sphereCenter);

	float Koe = Mu / (4 * MATH_PI);
	float dFi = 2 * MATH_PI / GenRadSplit;
	float dL = dFi * GenRadius;
	
	for (int i = 0; i < GenRadSplit; i++)
	{
		float fi = i*dFi;
		float xi = GenRadius * cos(fi);
		float yi = GenRadius * sin(fi);
		float ri = sqrt((ResDist - xi)*(ResDist - xi) + (ResDist - yi)*(ResDist - yi));
		efi += Koe * dL * cos(fi) / ri;
	}

	return efi;
}

vec3 getColor(float power)
{
	int i = 0;
	
	if (sphereColoringCount == 0)
		return vec3(0,1,0);


	if (power < 0.15)
		return vec3(0/255.0,0/255.0,145/255.0);
	if (power < 0.3)
		return vec3(0/255.0,0/255.0,85/255.0);
	if (power < 0.45)
		return vec3(85/255.0,85/255.0,255/255.0);
	if (power < 0.6)
		return vec3(120/255.0,200/255.0,255/255.0);
	if (power < 0.8)
		return vec3(150/255.0,255/255.0,225/255.0);
	if (power < 1)
		return vec3(150/255.0,225/255.0,120/150.0);
	if (power < 1.2)
		return vec3(255/255.0,225/255.0,120/255.0);
	if (power < 1.4)
		return vec3(225/255.0,150/255.0,100/255.0);
	if (power < 1.4)
		return vec3(225/255.0,0/255.0,100/255.0);
	if (power < 1.6)
		return vec3(225/255.0,100/255.0,0/255.0);
	return vec3(1,0,0);

	for(; i < sphereColoringCount; i++)
	{
		if (power < sphereColoring[i*4])
			return vec3(sphereColoring[i*4+1], sphereColoring[i*4+2], sphereColoring[i*4+3]);
	}
	
	return vec3(sphereColoring[(i-1)*4+1], sphereColoring[(i-1)*4+2], sphereColoring[(i-1)*4+3]);

}
void main()
{
	//vec3 center = vec3(centerCubeOut.x, centerCubeOut.y, centerCubeOut.z);

	//float r = abs(distance(pos, center))/(int(centerCubeOut.w) % 1000);
	//float g = abs(distance(pos, center))/(int(centerCubeOut.w / 1000) % 1000);
	//float b = abs(distance(pos, center))/(int(centerCubeOut.w / 1000 / 1000));
	// Алгоритм с расчетом по кажой стороне
	//color = vec4(r, g, b, 1);

	// Алгоритм со средней длинной
	//color = vec4(vec3(distance(pos, center)/centerCubeOut.w, distance(pos, center)/centerCubeOut.w, distance(pos, center))/centerCubeOut.w, 1);
	color = vec4(getColor(calcPower()),1);
}