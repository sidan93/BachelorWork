#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>

using namespace std;

/************************************** Defined Constants ***************************************/

/*************************************** Global Variables ***************************************/
/* Bachelor variables */

/* GLUT variables */
double yaw = 0.0, pit = 0.0 ;                 /* Euler angles of the viewing rotation */
double scale = 1.0 ;                          /* Scale factor */
double xcen = 0.0, ycen = 0.0, zcen = 0.0 ;   /* Coordinates of the point looked at */

int animate = 1 ;                             /* 0 - stop, 1 = go, 2 = single-step */

/******************************************* Functions ******************************************/

/* GLUT callbacks */

#define INPUT_LINE_LENGTH 80

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

void DisplayCallbackFunction ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;
	glColor3d ( 1.0, 1.0, 1.0 );

	glutSwapBuffers();
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
	xcen = 0.0 ;
	ycen = 0.0 ;
	zcen = 0.0 ;
	glTranslated ( xcen, ycen, zcen - 50.0 ) ;
}


void TimerCallbackFunction ( int value )
{
	glutTimerFunc ( 30, TimerCallbackFunction, 0 ) ;

	// TODO

	glutPostRedisplay () ;
}



/* The Main Program */

void initResources()
{
}

int main ( int argc, char *argv[] )
{
	int pargc = argc ;

	/* Initialize the random number generator */
	srand ( 1023 ) ;

	/* Set up the OpenGL parameters */
	glEnable ( GL_DEPTH_TEST ) ;
	glClearColor ( 0.0, 0.0, 0.0, 0.0 ) ;
	glClearDepth ( 1.0 ) ;

	/* Initialize GLUT */
	glutInit ( &pargc, argv ) ;
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;
	glutInitContextVersion(4, 0); // Init GL 4.0 context
	glutInitContextFlags(GLUT_CORE_PROFILE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize ( 600, 600 ) ;

	/* Create the window */
	glutCreateWindow ( "Bachelor Work" ) ;

	glewInit();
    printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	glutKeyboardFunc ( KeyboardCallbackFunction ) ;
	glutMouseFunc ( MouseCallbackFunction ) ;
	glutSpecialFunc ( SpecialKeyboardCallbackFunction ) ;
	glutDisplayFunc ( DisplayCallbackFunction ) ;
	glutReshapeFunc ( ReshapeCallbackFunction ) ;
	glutTimerFunc ( 30, TimerCallbackFunction, 0 ) ;

	initResources();

	/* Enter the GLUT main loop */
	glutMainLoop () ;

	return 0 ;
}

