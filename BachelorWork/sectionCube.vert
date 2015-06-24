#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

out vec3 pos;
out vec3 fragmentColor;

out vec3 pos1;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
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
	float ResDist = distance(position, sphereCenter);

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

void main(){

	// Output position of the vertex, in clip space : MVP * position
	pos = position;
	gl_Position =  MVP * vec4(position, 1);
	fragmentColor = getColor(calcPower());

	
}
