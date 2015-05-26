#include "Section.h"


Section::Section()
{
	name = "                                                     ";

	init();
	initShaders();
	initGeometry();
}

void Section::initCircuit() {

}

// TODO Сделать функцию и переменные static
void Section::init()
{
}

void Section::initShaders()
{
	shaderID = LoadShaders("section.vert", "section.frag");
	matrixID = glGetUniformLocation(shaderID, "MVP");

	textureID1 = glGetUniformLocation(shaderID, "mainSampler");

	AddTexture("texture01.jpg", textureID1);
}

void Section::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 0 * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);
}


void Section::Draw(float *MVP)
{
	if (!isEnable)
		return;

	glUseProgram(shaderID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, MVP);

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


	// Draw the triangle !
	glDrawArrays(GL_LINES, 0, 0 / 2);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}



Section::~Section()
{
}
