#include "Section.h"


Section::Section()
{
	name = "                                                     ";

	position.x = 50;
	position.y = 170;
	position.z = 400;
	step = 25;
	maxSize = vec3(2000, 2000, 2000);

	//init();
	initShaders();
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

void Section::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, countPoint * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);
}

void Section::Draw(float *MVP)
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
	glDrawArrays(GL_LINES, 0, countPoint / 2);

	glDisableVertexAttribArray(0);
}

void Section::Update() 
{

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
