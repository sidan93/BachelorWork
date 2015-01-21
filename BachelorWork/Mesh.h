#pragma once
#include <string>
#include "glm/glm.hpp"
#include <io.h>
#include "GL/glew.h"
#include "Helpers.h"
#include <memory>

using namespace std;
using namespace glm;

class Mesh
{
private:
	int MAX_VERTICES;
	int MAX_POLYGONS;

	int _countVectices;
	int _countPolygons;
	int _countMapcoord;

	vec3 *_vertex;
	vec3 *_polygon;
	vec2 *_mapcoord;

	GLfloat **_vertexList;
	GLfloat **_mapcoordList;

	string name;

	GLuint _texture;
	GLuint _textureID;
public:
	Mesh(void);

	bool Load3D(const char * file);
	bool LoadTexture(const char * file);

	GLfloat** getPointList() const;
	GLfloat** getMapCoordList() const;

	GLsizeiptr getSizePointList() const;
	GLsizeiptr getSizeMapCoordList() const;

	int CountVertex() const;
	int CountMapcoord() const;

	void init();

	~Mesh(void);
};

