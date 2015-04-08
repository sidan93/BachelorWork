#include "Parallelepiped.h"


Parallelepiped::Parallelepiped(vec3 position_, vec3 size_, int material_) : position(position_), _material(material_)
{
	name = "                                                     ";
	int scaleFactor = 50;
	position = vec3(position.x * scaleFactor, position.y * scaleFactor, position.z * scaleFactor);
	GlobalSize = vec3(size_.x * scaleFactor, size_.y * scaleFactor, size_.z * scaleFactor);
	size = vec3(size_.x / 2 * scaleFactor, size_.y / 2 * scaleFactor, size_.z / 2 * scaleFactor);

	init();
	initShaders();
	initGeometry();
}

// TODO Сделать функцию и переменные static
void Parallelepiped::init()
{
	_vertexList = new GLfloat[108];
	_mapcoordList = new GLfloat[72];
	_normalList = new GLfloat[108];
	int i = 0; // Номер треугольника 

	// https://ru.wikipedia.org/wiki/%D0%9F%D0%B0%D1%80%D0%B0%D0%BB%D0%BB%D0%B5%D0%BB%D0%B5%D0%BF%D0%B8%D0%BF%D0%B5%D0%B4
	// Z смотрит на нас 
	// TODO Не правильно выставлены нормали

	// Верхняя грань 
	// B1 A1 D1
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;
	// D1 C1 B1
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 1; _normalList[i * 3 + 2] = 0;

	// Нижняя грань 
	// A B C
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;

	// C D A
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = -1; _normalList[i * 3 + 2] = 0;

	// Передняя грань 
	// A1 A D
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	// D1 D A1
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;

	// Задняя грань 
	// B B1 C
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	// C1 C B1
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;

	// Левая грань
	// B A A1  
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	// B A1 B1
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = -1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;

	// Правая грань
	// D1 D C
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	// C1 D1 C
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = 1; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = 1; _vertexList[i * 3 + 2] = 1;
	_mapcoordList[i * 2] = 0; _mapcoordList[i * 2 + 1] = 1;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = 1;
	i++;
	_vertexList[i * 3] = 1; _vertexList[i * 3 + 1] = -1; _vertexList[i * 3 + 2] = -1;
	_mapcoordList[i * 2] = -1; _mapcoordList[i * 2 + 1] = 0;
	_normalList[i * 3] = 0; _normalList[i * 3 + 1] = 0; _normalList[i * 3 + 2] = -1;
}

void Parallelepiped::initShaders()
{
	shaderID = LoadShaders("cube.vert", "cube.frag");
	matrixID = glGetUniformLocation(shaderID, "MVP");
	shaderPosID = glGetUniformLocation(shaderID, "position");
	shaderSizeID = glGetUniformLocation(shaderID, "size");

	textureID1 = glGetUniformLocation(shaderID, "mainSampler");

	switch (_material) {
	case 1:
		AddTexture("texture02.jpg", textureID1);
		break;
	case 2:
		AddTexture("texture03.jpg", textureID1);
		break;
	default:
		AddTexture("texture01.jpg", textureID1);
		break;
	}
}

void Parallelepiped::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLuint), _vertexList, GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(GLuint), _mapcoordList, GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(GLuint), _normalList, GL_STATIC_DRAW);
}

void Parallelepiped::Draw(float *MVP, int displayType) 
{
	if (!isEnable)
		return;

	glUseProgram(shaderID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, MVP);
	glUniform3f(shaderPosID, position.x, position.y, position.z);
	glUniform3f(shaderSizeID, size.x, size.y, size.z);

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

	// 3nd attribute buffer : normal
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);


	// Draw the triangle !
	glDrawArrays(displayType, 0, 108 / 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

Parallelepiped::~Parallelepiped()
{
}
