#include "Section.h"


Section::Section(SectionSphere *sectionSphere_)
{
	name = "                                                     ";

	position.x = 50;
	position.y = 170;
	position.z = 400;
	step = 25;
	isEnableGridSection = true;
	isEnable = true;
	maxSize = vec3(2000, 2000, 2000);
	_vertexListSection = new GLfloat[10000];
	_vertexListSectionColor = new GLfloat[10000];
	_vertexListForCircuit = new GLfloat[10000];
	_vertexListCurcuitColor = new GLfloat[10000];

	sectionSphere = sectionSphere_;

	//init();
	initShaders();
	initShadersSection();
	//initGeometry();

}

void Section::initCircuit() {

}

void Section::Init()
{
	init();
	initGeometry();
}

// TODO Сделать функцию и переменные static
void Section::init()
{
	int iterX = maxSize.x / step + 1;
	int iterY = maxSize.y / step + 1;
	int iterZ = maxSize.z / step + 1;

	_vertexList = new GLfloat[iterZ*iterX * 6 + iterZ*iterY * 6 + iterX*iterY * 6];
	int i = 0;
	// Верикальные
	for (int z = 0; z < iterZ; z++)
		for (int x = 0; x < iterX && z == 0 || x < 1; x++)
		{
			// Низ
			_vertexList[i + 0] = position.x + x*step;
			_vertexList[i + 1] = position.y;
			_vertexList[i + 2] = position.z + z*step;
			// Верх
			_vertexList[i + 3] = position.x + x*step;
			_vertexList[i + 4] = position.y + maxSize.y;
			_vertexList[i + 5] = position.z + z*step;
			i += 6;
		}

	// Горизонтальные
	for (int z = 0; z < iterZ; z++)
		for (int y = 0; y < iterY && z == 0 || y < 1; y++)
		{
			// Лево
			_vertexList[i + 0] = position.x;
			_vertexList[i + 1] = position.y + y*step;
			_vertexList[i + 2] = position.z + z*step;
			// Право
			_vertexList[i + 3] = position.x + maxSize.x;
			_vertexList[i + 4] = position.y + y*step;
			_vertexList[i + 5] = position.z + z*step;
			i += 6;
		}

	// Уходящие
	for (int x = 0; x < iterX; x++)
		for (int y = 0; y < iterY && x == 0 || y < 1; y++)
		{
			// Лево
			_vertexList[i + 0] = position.x + x*step;
			_vertexList[i + 1] = position.y + y*step;
			_vertexList[i + 2] = position.z;
			// Право
			_vertexList[i + 3] = position.x + x*step;
			_vertexList[i + 4] = position.y + y*step;
			_vertexList[i + 5] = position.z + maxSize.z;
			i += 6;
		}


	countPoint = i;

}

void Section::initShaders()
{
	shaderID = LoadShaders("section.vert", "section.frag");
	matrixID = glGetUniformLocation(shaderID, "MVP");
}

void Section::initShadersSection()
{
	shaderCubeID = LoadShaders("sectionCube.vert", "sectionCube.frag");
	matrixCubeID = glGetUniformLocation(shaderID, "MVP");
}

void Section::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, countPoint * 2 * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);
}

void Section::initSectionGeomentry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexSectionbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexSectionbuffer);
	glBufferData(GL_ARRAY_BUFFER, countPointSection * 3 * sizeof(GLuint), _vertexListSection, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexSectionColorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexSectionColorbuffer);
	glBufferData(GL_ARRAY_BUFFER, countPointSection * 3 * sizeof(GLuint), _vertexListSectionColor, GL_STATIC_DRAW);

	glGenBuffers(2, &vertexbufferForCircuit);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbufferForCircuit);
	glBufferData(GL_ARRAY_BUFFER, countPointForCurcuit * 3 * sizeof(GLuint), _vertexListForCircuit, GL_STATIC_DRAW);

	glGenBuffers(2, &vertexCurcuitColorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexCurcuitColorbuffer);
	glBufferData(GL_ARRAY_BUFFER, countPointForCurcuit * 3 * sizeof(GLuint), _vertexListCurcuitColor, GL_STATIC_DRAW);
}

void Section::Draw(float *MVP)
{
	if (!isEnable)
		return;

	if (isEnableGridSection)
	{
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
		glDrawArrays(GL_LINES, 0, countPoint / 2);

		glDisableVertexAttribArray(0);
	}

	if (countPointSection != 0)
	{
		glUseProgram(shaderCubeID);
		glUniformMatrix4fv(matrixCubeID, 1, GL_FALSE, MVP);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexSectionbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glBindBuffer(GL_ARRAY_BUFFER, vertexSectionColorbuffer);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, countPointSection);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	if (countPointForCurcuit != 0)
	{
		glUseProgram(shaderCubeID);
		glUniformMatrix4fv(matrixCubeID, 1, GL_FALSE, MVP);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbufferForCircuit);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		glBindBuffer(GL_ARRAY_BUFFER, vertexCurcuitColorbuffer);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		// Draw the triangle !
		glDrawArrays(GL_LINES, 0, countPointForCurcuit);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}

float Section::_getCubeSizeForShaders(vec3 size) {
	// Алгоритм с расчетом по кажой стороне
	return (size.x + size.y * 1000 + size.z * 1000 * 1000);
	// Алгоритм со средней длинной
	return (size.x + size.y + size.z) / 3;
};
void Section::Update(vector<Parallelepiped*> lists)
{
	vec3 color__;
	int i = 0;

	float maxRightX = 0;
	float maxRightY = 0;
	float maxRightZ = 0;

	for (auto cube : lists)
	{
		// Верхняя грань 
		if (cube->position.y + cube->size.y >= position.y && cube->position.y - cube->size.y < position.y)
		{
			float leftX = cube->position.x - cube->size.x < position.x ? position.x : cube->position.x - cube->size.x;
			float rightX = cube->position.x + cube->size.x;
			float leftZ = cube->position.z - cube->size.z < position.z ? position.z : cube->position.z - cube->size.z;
			float rightZ = cube->position.z + cube->size.z;
			float centerX = leftX + (rightX - leftX) / 2;
			float centerZ = leftZ + (rightZ - leftZ) / 2;

			maxRightX = std::max(maxRightX, rightX);
			maxRightZ = std::max(maxRightZ, rightZ);

			// Против часов
			// Треугольник 1
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 2
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 3
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 4
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 5
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 6
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(rightX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 7
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 8
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(centerX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = position.y; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(leftX, position.y, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
		}

		// Левая грань
		if (cube->position.x + cube->size.x >= position.x && cube->position.x - cube->size.x < position.x)
		{
			float leftY = cube->position.y - cube->size.y < position.y ? position.y : cube->position.y - cube->size.y;
			float rightY = cube->position.y + cube->size.y;
			float leftZ = cube->position.z - cube->size.z < position.z ? position.z : cube->position.z - cube->size.z;
			float rightZ = cube->position.z + cube->size.z;	
			float centerY = leftY + (rightY - leftY) / 2;
			float centerZ = leftZ + (rightZ - leftZ) / 2;

			maxRightY = std::max(maxRightY, rightY);
			maxRightZ = std::max(maxRightZ, rightZ);

			// ПО часам
			// Треугольник 1
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 2
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 3
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 4
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = leftZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, leftZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 5
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 6
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, rightY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 7
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 8
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, centerY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = rightZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, rightZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = position.x; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = centerZ;
			color__ = sectionSphere->getColor(vec3(position.x, leftY, centerZ));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
		}
		// Задняя грань
		if (cube->position.z + cube->size.z >= position.z && cube->position.z - cube->size.z < position.z)
		{
			float leftX = cube->position.x - cube->size.x < position.x ? position.x : cube->position.x - cube->size.x;
			float rightX = cube->position.x + cube->size.x;
			float leftY = cube->position.y - cube->size.y < position.y ? position.y : cube->position.y - cube->size.y;
			float rightY = cube->position.y + cube->size.y;
			float centerX = leftX + (rightX - leftX) / 2;
			float centerY = leftY + (rightY - leftY) / 2;

			maxRightX = std::max(maxRightX, rightX);
			maxRightY = std::max(maxRightY, rightY);

			// Треугольник 1
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 2
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 3
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 4
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = leftY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, leftY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 5
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 6
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = rightX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(rightX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 7
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(centerX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			// Треугольник 8
			color__ = sectionSphere->getColor(vec3(centerX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			_vertexListSection[i * 3] = centerX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = rightY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, rightY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
			_vertexListSection[i * 3] = leftX; _vertexListSection[i * 3 + 1] = centerY; _vertexListSection[i * 3 + 2] = position.z;
			color__ = sectionSphere->getColor(vec3(leftX, centerY, position.z));
			_vertexListSectionColor[i * 3 + 0] = color__.x; _vertexListSectionColor[i * 3 + 1] = color__.y; _vertexListSectionColor[i * 3 + 2] = color__.z;
			i++;
		}
	}
	countPointSection = i;

	i = 0;
	vec3 colorC = vec3(0, 1, 0);
	_vertexListForCircuit[i * 3 + 0] = position.x + 5; _vertexListForCircuit[i * 3 + 1] = position.y + 5; _vertexListForCircuit[i * 3 + 2] = position.z + 5;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;
	_vertexListForCircuit[i * 3 + 0] = position.x + maxRightX; _vertexListForCircuit[i * 3 + 1] = position.y + 5; _vertexListForCircuit[i * 3 + 2] = position.z + 5;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;

	_vertexListForCircuit[i * 3 + 0] = position.x + 5; _vertexListForCircuit[i * 3 + 1] = position.y + 5; _vertexListForCircuit[i * 3 + 2] = position.z + 5;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;
	_vertexListForCircuit[i * 3 + 0] = position.x + 5; _vertexListForCircuit[i * 3 + 1] = position.y + maxRightY; _vertexListForCircuit[i * 3 + 2] = position.z + 5;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;

	_vertexListForCircuit[i * 3 + 0] = position.x + 5; _vertexListForCircuit[i * 3 + 1] = position.y + 5; _vertexListForCircuit[i * 3 + 2] = position.z + 5;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;
	_vertexListForCircuit[i * 3 + 0] = position.x + 5; _vertexListForCircuit[i * 3 + 1] = position.y + 5; _vertexListForCircuit[i * 3 + 2] = position.z + maxRightZ;
	_vertexListCurcuitColor[i * 3 + 0] = colorC.x; _vertexListCurcuitColor[i * 3 + 1] = colorC.y; _vertexListCurcuitColor[i * 3 + 2] = colorC.z;
	i++;

	countPointForCurcuit = i;

	initSectionGeomentry();
}

vec3 Section::getPosition() const {
	return position;
}
void Section::setMaxSize(vec3 maxSize_) {
	maxSize = maxSize_;
}

Section::~Section()
{
}
