#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Helpers.h"
#include "Camera.h"
#include "Mesh.h"

using namespace std;

/************************************** Defined Constants ***************************************/

/*************************************** Global Variables ***************************************/
/* GLUT variables */

/* Shaders variables */

/* Bachelor variables */

GLuint shaderID;

GLuint matrixID;

GLuint textureID;
GLuint Texture;

Camera *camera;
Mesh *mesh;
/******************************************* Functions ******************************************/

void CreateGeometry()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // Треугольник 1 : начало
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // Треугольник 1 : конец
		1.0f, 1.0f,-1.0f, // Треугольник 2 : начало
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // Треугольник 2 : конец
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	
	static const GLfloat g_uv_buffer_data[] = { 
		0.000059f, 1.0f-0.000004f, 
		0.000103f, 1.0f-0.336048f, 
		0.335973f, 1.0f-0.335903f, 
		1.000023f, 1.0f-0.000013f, 
		0.667979f, 1.0f-0.335851f, 
		0.999958f, 1.0f-0.336064f, 
		0.667979f, 1.0f-0.335851f, 
		0.336024f, 1.0f-0.671877f, 
		0.667969f, 1.0f-0.671889f, 
		1.000023f, 1.0f-0.000013f, 
		0.668104f, 1.0f-0.000013f, 
		0.667979f, 1.0f-0.335851f, 
		0.000059f, 1.0f-0.000004f, 
		0.335973f, 1.0f-0.335903f, 
		0.336098f, 1.0f-0.000071f, 
		0.667979f, 1.0f-0.335851f, 
		0.335973f, 1.0f-0.335903f, 
		0.336024f, 1.0f-0.671877f, 
		1.000004f, 1.0f-0.671847f, 
		0.999958f, 1.0f-0.336064f, 
		0.667979f, 1.0f-0.335851f, 
		0.668104f, 1.0f-0.000013f, 
		0.335973f, 1.0f-0.335903f, 
		0.667979f, 1.0f-0.335851f, 
		0.335973f, 1.0f-0.335903f, 
		0.668104f, 1.0f-0.000013f, 
		0.336098f, 1.0f-0.000071f, 
		0.000103f, 1.0f-0.336048f, 
		0.000004f, 1.0f-0.671870f, 
		0.336024f, 1.0f-0.671877f, 
		0.000103f, 1.0f-0.336048f, 
		0.336024f, 1.0f-0.671877f, 
		0.335973f, 1.0f-0.335903f, 
		0.667969f, 1.0f-0.671889f, 
		1.000004f, 1.0f-0.671847f, 
		0.667979f, 1.0f-0.335851f
	};

	mesh->initGeometry();
}

/* GLUT callbacks */

void DisplayCallbackFunction ( void )
{
	//Clear all the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	camera->Update();

	glUseProgram(shaderID);

	glEnable(GL_TEXTURE0);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &camera->MVP[0][0]);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

	mesh->Draw();

	glutSwapBuffers();
}

void TimerCallbackFunction ( int value )
{
	glutTimerFunc ( 30, TimerCallbackFunction, 0 ) ;

	// TODO

	glutPostRedisplay () ;
}

void KeyboardCallbackFunction ( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 27 :  /* Escape key */
		glutLeaveMainLoop () ;
		break ;
	case 'q':
		camera->_position.x ++;
		break;
	case 'a':
		camera->_position.x --;
		break;
	case 'w':
		camera->_position.y ++;
		break;
	case 's':
		camera->_position.y --;
		break;
	case 'e':
		camera->_position.z ++;
		break;
	case 'd':
		camera->_position.z --;
		break;
	camera->Update();
	}
}

void SpecialKeyboardCallbackFunction ( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_UP :  /* Rotate up a little */
		break ;
	}

	glutPostRedisplay () ;
}

void MouseCallbackFunction ( int button, int updown, int x, int y )
{
	if ( updown == GLUT_UP )
	{

	}
}

void ReshapeCallbackFunction ( int width, int height )
{
	float ar;
	glViewport ( 0, 0, width, height ) ;
	glMatrixMode ( GL_PROJECTION ) ;
	glLoadIdentity () ;
	ar = (float) width / (float) height ;
	glFrustum ( -ar, ar, -1.0, 1.0, 10.0, 100.0 ) ;
	glMatrixMode ( GL_MODELVIEW ) ;
	glLoadIdentity () ;
}

/* Init functions */

void InitGLStates()
{
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(0,0,0,0);
	glClearDepth(1.0);
	glClearStencil(0);
	//glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	//glDisable(GL_DITHER);
	//glActiveTexture(GL_TEXTURE0);
}

void InitShaders()
{
	shaderID = LoadShaders("Shader1.vert", "Shader1.frag");
	matrixID = glGetUniformLocation(shaderID, "MVP");
	textureID  = glGetUniformLocation(shaderID, "myTextureSampler");
}

bool InitOther()
{
	camera = new Camera();
	Texture = loadBMP_custom("sun_tex.bmp");

	mesh = new Mesh();
	bool load = mesh->Load3D("table.3DS");
	mesh->init();

	return true;
}

/* The Main Program */
int main ( int argc, char *argv[] )
{
	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_CORE_PROFILE);
	glutInitContextProfile(GLUT_CORE_PROFILE);


	glutInitWindowSize ( 600, 600 ) ;

	/* Create the window */
	glutCreateWindow ( "Bachelor Work" ) ;
	
	/* Initialize GLEW */
	glewExperimental=TRUE;
	glewInit();
	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	/* Initialize all objects */
	InitGLStates();
	InitShaders();
	bool err = InitOther();
	if (err == true) {
		CreateGeometry();
	}

	/* Initialize CALLBACK functions */
	glutKeyboardFunc	( KeyboardCallbackFunction ) ;
	glutMouseFunc		( MouseCallbackFunction ) ;
	glutSpecialFunc		( SpecialKeyboardCallbackFunction ) ;
	glutDisplayFunc		( DisplayCallbackFunction ) ;
	glutReshapeFunc		( ReshapeCallbackFunction ) ;
	glutTimerFunc		( 30, TimerCallbackFunction, 0 ) ;

	/* Enter the GLUT main loop */
	glutMainLoop () ;

	return 0 ;
}