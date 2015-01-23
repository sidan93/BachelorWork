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
	// Our vertex type
	struct vertex_type{
		float x,y,z;
	};

	// The polygon (triangle), 3 numbers that aim 3 vertices
	struct polygon_type{
		int a,b,c;
	};

	// The mapcoord type, 2 texture coordinates for each vertex
	struct mapcoord_type{
		float u,v;
	};

private:

	int _countVectices;
	int _countPolygons;
	int _countMapcoord;

	vertex_type *_vertex;
	polygon_type *_polygon;
	mapcoord_type *_mapcoord;

	GLfloat *_vertexList;
	GLfloat *_mapcoordList;

	string name;

	GLuint _texture;
	GLuint _textureID;

	GLuint vertexbuffer;
	GLuint vertexArrays;
	GLuint uvbuffer;
public:
	Mesh(void);

	bool Load3D(const char * file);
	bool LoadTexture(const char * file);

	GLfloat* getPointList() const;
	GLfloat* getMapCoordList() const;

	GLsizeiptr getSizePointList() const;
	GLsizeiptr getSizeMapCoordList() const;

	int CountVertex() const;
	int CountMapcoord() const;

	void init();
	void Draw();
	void initGeometry();

	~Mesh(void);
};

