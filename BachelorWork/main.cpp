#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Helpers.h"

using namespace std;

/************************************** Defined Constants ***************************************/


/*************************************** Global Variables ***************************************/
/* GLUT variables */

/* Shaders variables */

/* Bachelor variables */

GLuint shaderID;
GLuint vertexbuffer;
GLuint vertexArrays;
/******************************************* Functions ******************************************/

void CreateGeometry()
{
	//glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_SHORT, NULL);
	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenVertexArrays(1, &vertexArrays);
	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBindVertexArray(vertexArrays);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void CreateGeometrySphere() {}

/* GLUT callbacks */

void DisplayCallbackFunction ( void )
{
	//Clear all the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glUseProgram(shaderID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
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
	if ( updown == GLUT_DOWN )
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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);
	glActiveTexture(GL_TEXTURE0);
}

void InitShaders()
{
	shaderID = LoadShaders("Shader1.vert", "Shader1.frag");
}

/* The Main Program */
int main ( int argc, char *argv[] )
{
	/* Set up the OpenGL parameters */
	glEnable ( GL_DEPTH_TEST ) ;
	glClearColor ( 0.0, 0.0, 0.0, 0.0 ) ;
	glClearDepth ( 1.0 ) ;

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

	CreateGeometry();

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