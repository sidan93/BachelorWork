#include "includes.h"

#include "Helpers.h"
#include "Camera.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Texture.h"
#include "Parallelepiped.h"

using namespace std;

/************************************** Defined Constants ***************************************/

/*************************************** Global Variables ***************************************/
/* GLUT variables */

/* Shaders variables */

/* Bachelor variables */

Camera *camera;
//Mesh *mesh;
//SkyBox *skyBox;
vector<Parallelepiped*> cubes;

int displayType = 0;
/******************************************* Functions ******************************************/

void CreateGeometry()
{
}

/* GLUT callbacks */

void DisplayCallbackFunction ( void )
{
	//Clear all the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	camera->Update();
	for (auto cube : cubes)
		cube->Draw(&camera->MVP[0][0], displayType);

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
	case 't':
		camera->_target.x ++;
		break;
	case 'g':
		camera->_target.x --;
		break;
	case 'y':
		camera->_target.y ++;
		break;
	case 'h':
		camera->_target.y --;
		break;
	case 'u':
		camera->_target.z ++;
		break;
	case 'j':
		camera->_target.z --;
		break;
	case '1':
		displayType = GL_POINTS;
		break;
	case '2':
		displayType = GL_LINES;
		break;
	case '3':
		displayType = GL_LINE_STRIP;
		break;
	case '4':
		displayType = GL_LINE_LOOP;
		break;
	case '5':
		displayType = GL_LINE_STRIP_ADJACENCY;
		break;
	case '6':
		displayType = GL_LINES_ADJACENCY;
		break;
	case '7':
		displayType = GL_TRIANGLES;
		break;
	case '8':
		displayType = GL_TRIANGLE_STRIP;
		break;
	case '9':
		displayType = GL_TRIANGLE_FAN;
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
	glEnable(GL_TEXTURE0);
	//glDisable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);
	//glDisable(GL_DITHER);
	//glActiveTexture(GL_TEXTURE0);
}

bool InitOther()
{
	camera = new Camera();
	
	//mesh = new Mesh("ElephantBody.3ds");
	//mesh->AddTexture("texture01.jpg", textureID1);
	//mesh->AddTexture("sun_tex.bmp", textureID1);

	ifstream input("cubes.api");
	int count;
	input >> count;
	for (int i = 0; i < count; i++)
	{
		vec3 position, size;
		input >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
		cubes.push_back(new Parallelepiped(position, size));
	}

	return true;
}

/* The Main Program */
int main ( int argc, char *argv[] )
{
	/* Initialize GLUT */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitContextVersion(3, 3);
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
	bool init_ = InitOther();
	if (init_  == true) {
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