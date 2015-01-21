#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

GLuint loadBMP_custom(const char * imagepath);

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);