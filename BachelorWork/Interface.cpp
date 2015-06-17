#include "Interface.h"


Interface::Interface()
{
	isEnable = true;

	init();
	//initCircuit();
	initShaders();
	initGeometry();
}

// TODO —делать функцию и переменные static
void Interface::init()
{
	_vertexList = new GLfloat[36];
	_mapcoordList = new GLfloat[24];

	float leftCamera = -0.98;
	float rightCamera = -0.78;
	float topCamera = 0.98;
	float bottomCamera = 0.84;
	float maxx = -1;

	int i = 0;
	// ѕередн€€ грань 
	// A1 A D
	_vertexList[i * 3] = leftCamera; _vertexList[i * 3 + 1] = topCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	i++;
	_vertexList[i * 3] = leftCamera; _vertexList[i * 3 + 1] = bottomCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	i++;
	_vertexList[i * 3] = rightCamera; _vertexList[i * 3 + 1] = bottomCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	// D1 D A1
	i++;
	_vertexList[i * 3] = rightCamera; _vertexList[i * 3 + 1] = bottomCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	i++;
	_vertexList[i * 3] = rightCamera; _vertexList[i * 3 + 1] = topCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	i++;
	_vertexList[i * 3] = leftCamera; _vertexList[i * 3 + 1] = topCamera; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	i++;

	float leftSection = 0.78;
	float rightSection = 0.98;
	float topSection = 0.98;
	float bottomSection = 0.84;
	// ѕередн€€ грань 
	// A1 A D
	_vertexList[i * 3] = leftSection; _vertexList[i * 3 + 1] = topSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	i++;
	_vertexList[i * 3] = leftSection; _vertexList[i * 3 + 1] = bottomSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	i++;
	_vertexList[i * 3] = rightSection; _vertexList[i * 3 + 1] = bottomSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	// D1 D A1
	i++;
	_vertexList[i * 3] = rightSection; _vertexList[i * 3 + 1] = bottomSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	i++;
	_vertexList[i * 3] = rightSection; _vertexList[i * 3 + 1] = topSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	i++;
	_vertexList[i * 3] = leftSection; _vertexList[i * 3 + 1] = topSection; _vertexList[i * 3 + 2] = maxx;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
}

void Interface::initShaders()
{
	shaderID = LoadShaders("interface.vert", "interface.frag");

	textureID1 = glGetUniformLocation(shaderID, "mainSampler");

	AddTexture("button02.jpg", textureID1);
}

void Interface::initGeometry()
{
	// ћаги€ без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLuint), _mapcoordList, GL_STATIC_DRAW);
}
void Interface::initCircuit()
{
}

void Interface::Draw() 
{
	if (!isEnable)
		return;

	glUseProgram(shaderID);

	int index = 0;
	map<const char*, Texture*>::iterator item;
	for (item = _texture.begin(), index; item != _texture.end(); item++, index++)
		item->second->BindTexture(index);

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

	// 2nd attribute buffer : uv
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

Interface::~Interface()
{
}
