#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>
#include <stdio.h>
#include "Helpers.h"

using namespace std;

/************************************** Defined Constants ***************************************/

#define BUFFER_OFFSET(i) ((void*)(i))

//Vertex, tex0
//
//SIZE : 4+4+4 +4+4 = 4*6 = 20 bytes
//It's better to make it multiple of 32
//32-20 = 12 bytes (of garbage should be added)
//12/4 = 3 floats should be added
struct TVertex_VT
{
	float	x, y, z;
	float	s0, t0;
	float	padding[3];
};

//Vertex, normal, tex0
//
//SIZE : 4+4+4 +4+4+4 +4+4 = 4*8 = 32 bytes
struct TVertex_VNT
{
	float	x, y, z;
	float	nx, ny, nz;
	float	s0, t0;
};

//Vertex, color
//
//SIZE : 4+4+4 +4 = 4*4 = 16 bytes
//It's better to make it multiple of 32
//32-16 = 16 bytes (of garbage should be added)
//16/4 = 4 floats should be added
struct TVertex_VC
{
	float	x, y, z;
	unsigned int	color;
	float	padding[4];
};

/*************************************** Global Variables ***************************************/
/* GLUT variables */

/* Shaders variables */
GLuint	ShaderProgram[2];
GLuint	VertexShader[2];
GLuint	FragmentShader[2];

int ProjectionModelviewMatrix_Loc[2];		//The location of ProjectionModelviewMatrix in the shaders

/* Bachelor variables */

//A quad
GLushort	pindex_quad[6];
TVertex_VC	pvertex_quad[4];

//A triangle
GLushort		pindex_triangle[3];
TVertex_VNT		pvertex_triangle[3];

//1 VAO for the quad
//1 VAO for the triangle
GLuint VAOID[2];
//1 IBO for the quad (Index Buffer Object)
//1 IBO for the triangle
GLuint IBOID[2];
//1 IBO for the quad (Vertex Buffer Object)
//1 IBO for the triangle
GLuint VBOID[2];
/******************************************* Functions ******************************************/

void CreateGeometry()
{
	//A quad
	pvertex_quad[0].x=-0.8f;
	pvertex_quad[0].y=-0.5f;
	pvertex_quad[0].z=-0.9f;
	pvertex_quad[0].color=0xFFFFFFFF;

	pvertex_quad[1].x=0.0f;
	pvertex_quad[1].y=-0.5f;
	pvertex_quad[1].z=-0.9f;
	pvertex_quad[1].color=0xFFFF0000;

	pvertex_quad[2].x=-0.8f;
	pvertex_quad[2].y=0.5f;
	pvertex_quad[2].z=-0.9f;
	pvertex_quad[2].color=0xFF00FF00;

	pvertex_quad[3].x=0.0f;
	pvertex_quad[3].y=0.5f;
	pvertex_quad[3].z=-0.9f;
	pvertex_quad[3].color=0xFF0000FF;

	pindex_quad[0]=0;
	pindex_quad[1]=1;
	pindex_quad[2]=2;
	pindex_quad[3]=2;
	pindex_quad[4]=1;
	pindex_quad[5]=3;

	//The triangle
	pvertex_triangle[0].x=0.0f;
	pvertex_triangle[0].y=0.5f;
	pvertex_triangle[0].z=-1.0f;
	pvertex_triangle[0].nx=0.0f;
	pvertex_triangle[0].ny=0.0f;
	pvertex_triangle[0].nz=1.0f;
	pvertex_triangle[0].s0=0.0f;
	pvertex_triangle[0].t0=0.0f;

	pvertex_triangle[1].x=0.3f;
	pvertex_triangle[1].y=-0.5f;
	pvertex_triangle[1].z=-1.0f;
	pvertex_triangle[1].nx=0.0f;
	pvertex_triangle[1].ny=0.0f;
	pvertex_triangle[1].nz=1.0f;
	pvertex_triangle[1].s0=1.0f;
	pvertex_triangle[1].t0=0.0f;

	pvertex_triangle[2].x=0.8f;
	pvertex_triangle[2].y=0.5f;
	pvertex_triangle[2].z=-1.0f;
	pvertex_triangle[2].nx=0.0f;
	pvertex_triangle[2].ny=0.0f;
	pvertex_triangle[2].nz=1.0f;
	pvertex_triangle[2].s0=0.5f;
	pvertex_triangle[2].t0=1.0f;

	pindex_triangle[0]=0;
	pindex_triangle[1]=1;
	pindex_triangle[2]=2;


	//Create the IBO for the quad
	//16 bit indices
	glGenBuffers(1, &IBOID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), pindex_quad, GL_STATIC_DRAW);

	GLenum error=glGetError();

	//Create the IBO for the triangle
	//16 bit indices
	//We could have actually made one big IBO for both the quad and triangle.
	glGenBuffers(1, &IBOID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLushort), pindex_triangle, GL_STATIC_DRAW);

	error=glGetError();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	error=glGetError();

	//Create VBO for the quad
	glGenBuffers(1, &VBOID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
	glBufferData(GL_ARRAY_BUFFER, 4*sizeof(TVertex_VC), pvertex_quad, GL_STATIC_DRAW);

	error=glGetError();

	//Just testing
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Create VBO for the triangle
	glGenBuffers(1, &VBOID[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(TVertex_VNT), pvertex_triangle, GL_STATIC_DRAW);

	//Just testing
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	error=glGetError();

	//VAO for the quad *********************
	glGenVertexArrays(1, &VAOID[0]);
	glBindVertexArray(VAOID[0]);

	//Bind the VBO and setup pointers for the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VC), BUFFER_OFFSET(0));
	glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(TVertex_VC), BUFFER_OFFSET(sizeof(float)*3));
	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	//Bind the IBO for the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[0]);

	//Second VAO setup *******************
	//This is for the triangle
	glGenVertexArrays(1, &VAOID[1]);
	glBindVertexArray(VAOID[1]);

	//Bind the VBO and setup pointers for the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(sizeof(float)*3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TVertex_VNT), BUFFER_OFFSET(sizeof(float)*6));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	//Bind the IBO for the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOID[1]);

	//Just testing
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* GLUT callbacks */

void DisplayCallbackFunction ( void )
{
	float projectionModelviewMatrix[16];

	//Just set it to identity matrix
	memset(projectionModelviewMatrix, 0, sizeof(float)*16);
	projectionModelviewMatrix[0]=1.0;
	projectionModelviewMatrix[5]=1.0;
	projectionModelviewMatrix[10]=1.0;
	projectionModelviewMatrix[15]=1.0;

	//Clear all the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//Bind the shader that we want to use
	glUseProgram(ShaderProgram[0]);
	//Setup all uniforms for your shader
	glUniformMatrix4fv(ProjectionModelviewMatrix_Loc[0], 1, FALSE, projectionModelviewMatrix);
	//Bind the VAO
	glBindVertexArray(VAOID[0]);
	//At this point, we would bind textures but we aren't using textures in this example

	//Draw command
	//The first to last vertex is 0 to 3
	//6 indices will be used to render the 2 triangles. This make our quad.
	//The last parameter is the start address in the IBO => zero
	glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_SHORT, NULL);

	//Bind the shader that we want to use
	glUseProgram(ShaderProgram[1]);
	//Setup all uniforms for your shader
	glUniformMatrix4fv(ProjectionModelviewMatrix_Loc[1], 1, FALSE, projectionModelviewMatrix);
	//Bind the VAO
	glBindVertexArray(VAOID[1]);
	//At this point, we would bind textures but we aren't using textures in this example

	//Draw command
	//The first to last vertex is 0 to 3
	//3 indices will be used to render 1 triangle.
	//The last parameter is the start address in the IBO => zero
	glDrawRangeElements(GL_TRIANGLES, 0, 3, 3, GL_UNSIGNED_SHORT, NULL);

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
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);
	glActiveTexture(GL_TEXTURE0);
}

void InitShaders()
{
	if(LoadShader("Shader1.vert", "Shader1.frag", false, false, true, ShaderProgram[0], VertexShader[0], FragmentShader[0])==-1)
	{
		exit(1);
	}
	else
	{
		ProjectionModelviewMatrix_Loc[0]=glGetUniformLocation(ShaderProgram[0], "ProjectionModelviewMatrix");
	}

	if(LoadShader("Shader2.vert", "Shader2.frag", true, true, false, ShaderProgram[1], VertexShader[1], FragmentShader[1])==-1)
	{
		exit(1);
	}
	else
	{
		ProjectionModelviewMatrix_Loc[1]=glGetUniformLocation(ShaderProgram[1], "ProjectionModelviewMatrix");
	}
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