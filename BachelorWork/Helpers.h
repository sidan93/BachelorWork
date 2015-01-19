#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string loadFile(const char *fname);

void printShaderInfoLog(GLint shader);

int LoadShader(
	const char *pfilePath_vs, 
	const char *pfilePath_fs, 
	bool bindTexCoord0, 
	bool bindNormal, 
	bool bindColor, 
	GLuint &shaderProgram, 
	GLuint &vertexShader, 
	GLuint &fragmentShader);
