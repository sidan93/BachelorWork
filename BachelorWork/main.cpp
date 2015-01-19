#include <GL/glew.h>
#include <GL/freeglut.h>

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

void key_cb ( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 27 :  /* Escape key */
		glutLeaveMainLoop () ;
		break ;
	}
}

void special_cb ( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_UP :  /* Rotate up a little */
		break ;
	}

	glutPostRedisplay () ;
}

void mouse_cb ( int button, int updown, int x, int y )
{
	if ( updown == GLUT_DOWN )
	{
	}
}

void display_cb ( void )
{
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;

	glColor3d ( 1.0, 1.0, 1.0 ) ;  /* White */

	/* Draw some axes */
	glBegin ( GL_LINES ) ;
	glVertex3d ( 0.0, 0.0, 0.0 ) ;
	glVertex3d ( 2.0, 0.0, 0.0 ) ;
	glVertex3d ( 0.0, 0.0, 0.0 ) ;
	glVertex3d ( 0.0, 1.0, 0.0 ) ;
	glVertex3d ( 0.0, 0.0, 0.0 ) ;
	glVertex3d ( 0.0, 0.0, 1.0 ) ;
	glEnd () ;

	glutSwapBuffers();
}

void reshape_cb ( int width, int height )
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


void timer_cb ( int value )
{
	glutTimerFunc ( 30, timer_cb, 0 ) ;

	// TODO

	glutPostRedisplay () ;
}



/* The Main Program */

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
	glutInitWindowSize ( 600, 600 ) ;
	glutInit ( &pargc, argv ) ;
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;

	/* Create the window */
	glutCreateWindow ( "Bachelor Work" ) ;
	glutKeyboardFunc ( key_cb ) ;
	glutMouseFunc ( mouse_cb ) ;
	glutSpecialFunc ( special_cb ) ;
	glutDisplayFunc ( display_cb ) ;
	glutReshapeFunc ( reshape_cb ) ;
	glutTimerFunc ( 30, timer_cb, 0 ) ;

	/* Enter the GLUT main loop */
	glutMainLoop () ;

	return 0 ;
}

