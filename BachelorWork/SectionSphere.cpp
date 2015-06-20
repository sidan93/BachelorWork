#include "SectionSphere.h"


SectionSphere::SectionSphere()
{
	isEnable = true;
	_vertexList = new GLfloat[500000];

	initShaders();
}

vec3 SectionSphere::getColor(vec3 target)
{
	float range = glm::distance(target, center);
	float power = (maxPower - minPower) * (range / radius) + minPower;

	if (power < coloring[0].first)
		return coloring[0].second;
	
	if (power > coloring[coloring.size() - 1].first)
		return coloring[coloring.size() - 1].second;

	int index = 0;	
	for (int i = 0; i < coloring.size(); i++) {
		if (power < coloring[i].first)
		{
			index = i - 1;
			break;
		}
	}

	return coloring[index].second;

	float lengthWeight = coloring[index + 1].first - coloring[index].first;
	float leftWeight = (power - coloring[index].first) / lengthWeight;
	float rightWeight = (coloring[index + 1].first - power) / lengthWeight;
	
	if (leftWeight < rightWeight)
		return vec3(coloring[index].second.r * leftWeight, coloring[index].second.g * leftWeight, coloring[index].second.b * leftWeight);
	else 
		return vec3(coloring[index + 1].second.r * rightWeight, coloring[index + 1].second.g * rightWeight, coloring[index + 1].second.b * rightWeight);
		
	float r = coloring[index].second.r * leftWeight + coloring[index + 1].second.r + rightWeight;
	float g = coloring[index].second.g * leftWeight + coloring[index + 1].second.g + rightWeight;
	float b = coloring[index].second.b * leftWeight + coloring[index + 1].second.b + rightWeight;
	return vec3(r, g, b);
}

bool SortColoring(Coloring first, Coloring second)
{
	if (first.first < second.first)
		return true;
	return false;
}

void SectionSphere::Update()
{
	init();
	initGeometry();
}

void SectionSphere::init()
{
	int step = 10;
	int i = 0;
	double cosAngle1, cosAngle2, sinAngle1, sinAngle2;

	for (int V = 0; V < 360; V += step)
	{
		for (int U = 0; U < 360; U += step)
		{
			_vertexList[i + 0] = center.x + radius * cos(U * MATH_PI_ANGLE) * cos(V * MATH_PI_ANGLE);
			_vertexList[i + 1] = center.y + radius * sin(U * MATH_PI_ANGLE) * cos(V * MATH_PI_ANGLE);
			_vertexList[i + 2] = center.z + radius * sin(V * MATH_PI_ANGLE);
			//_vertexList[i + 3] = center.x + radius * cos(U * MATH_PI_ANGLE) * cos(V * MATH_PI_ANGLE);
			//_vertexList[i + 4] = center.y + newRadius * sinAngle2;
			//_vertexList[i + 5] = center.z + shift;
			i += 3;
		}
	}
	pointCount = i;
}
void SectionSphere::initCircuit()
{

}
void SectionSphere::initShaders()
{
	shaderID = LoadShaders("sectionSphere.vert", "sectionSphere.frag");
	matrixID = glGetUniformLocation(shaderID, "MVP");
}
void SectionSphere::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, pointCount  * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);
}

void SectionSphere::Draw(float *MVP)
{
	if (!isEnable)
		return;

	glUseProgram(shaderID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, MVP);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	// Draw the triangle !
	glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, pointCount / 2);

	glDisableVertexAttribArray(0);
}

void SectionSphere::readColoring()
{
	ifstream file("coloring.api");
	float power;
	float r, g, b;

	do {
		file >> power >> r >> g >> b;
		coloring.push_back(Coloring(power, vec3(r / 255.0, b / 255.0, g / 255.0)));
	} while (!file.eof());
	
	sort(coloring.begin(), coloring.end(), SortColoring);
}

SectionSphere::~SectionSphere()
{
}
