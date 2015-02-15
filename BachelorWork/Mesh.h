#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"

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

	vector<GLfloat*> _vertexList;
	vector<GLfloat*> _mapcoordList;
	vector<GLfloat*> _normalList;
	vector<int> _countVertexList;
	vector<int> _countMapcoordList;
	vector<int> _countNormalList;

	string name;

	map<const char*, Texture*> _texture;

	GLuint vertexArrays;
	vector<GLuint> vertexbuffer;
	vector<GLuint> uvbuffer;
	vector<GLuint> normalbuffer;

	int _drawType;
private:
	bool Load3D(const char * file);
	void init();
	void initGeometry();
public:
	Mesh(const char *meshFile);

	void AddTexture(const char *textureFile, GLuint shaderTextureId);

	void Draw();
	void setDrawType(int type);

	~Mesh(void);
};

