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

	vector<int> _countVectices;
	vector<int> _countPolygons;
	vector<int> _countMapcoord;

	vector<vertex_type*> _vertex;
	vector<polygon_type*> _polygon;
	vector<mapcoord_type*> _mapcoord;

	GLfloat* _vertexList;
	GLfloat* _mapcoordList;
	int _countVertexList;
	int _countMapcoordList;

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

	GLsizeiptr getSizePointList() const;
	GLsizeiptr getSizeMapCoordList() const;

	void init();
	void Draw();
	void initGeometry();

	~Mesh(void);
};

