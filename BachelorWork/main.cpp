#include "includes.h"

#include "Helpers.h"
#include "Camera.h"
#include "Mesh.h"
#include "SkyBox.h"
#include "Texture.h"
#include "Parallelepiped.h"
#include "Grid.h"

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
vector<Parallelepiped*> layers;
vector<Grid*> grids;

int displayType = GL_TRIANGLES;
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
	for (auto layer : layers)
		layer->Draw(&camera->MVP[0][0], GL_LINE_STRIP_ADJACENCY);
	for (auto grid : grids)
		grid->Draw(&camera->MVP[0][0], vec3(grids[0]->getCenter()));
	glutSwapBuffers();
}

void TimerCallbackFunction ( int value )
{
	glutTimerFunc ( 30, TimerCallbackFunction, 0 ) ;

	// TODO
	glutPostRedisplay () ;
}
void ConsoleUsage() {
	string value;
	cout << "Enter command:" << endl;
	cin >> value;

	if (value == "grid")
	{
		float alpha;
		cout << "Enter alpha" << endl;
		cin >> alpha;
		grids[0]->setAlpha(alpha);
	}
}
void KeyboardCallbackFunction ( unsigned char key, int x, int y )
{
	int addSpeed = 50;
	switch ( key )
	{
	case 27 :  /* Escape key */
		glutLeaveMainLoop () ;
		break ;
	case 'q':
		camera->_position.x += addSpeed;
		break;
	case 'a':
		camera->_position.x -= addSpeed;
		break;
	case 'w':
		camera->_position.y += addSpeed;
		break;
	case 's':
		camera->_position.y -= addSpeed;
		break;
	case 'e':
		camera->_position.z += addSpeed;
		break;
	case 'd':
		camera->_position.z -= addSpeed;
		break;
	case 't':
		camera->_target.x += addSpeed;
		break;
	case 'g':
		camera->_target.x -= addSpeed;
		break;
	case 'y':
		camera->_target.y += addSpeed;
		break;
	case 'h':
		camera->_target.y -= addSpeed;
		break;
	case 'u':
		camera->_target.z += addSpeed;
		break;
	case 'j':
		camera->_target.z -= addSpeed;
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
	case 'z':
		if (grids.size() > 0)
			grids[0]->isEnable = !grids[0]->isEnable;
		break;
	case 'c':
		ConsoleUsage();
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
	glFrustum ( -ar, ar, -1.0, 1.0, 10.0, 1000.0 ) ;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DITHER);
}

bool InitGrid()
{
	vector<int> pointX;
	vector<int> pointY;
	vector<int> pointZ;
	pointX.clear();
	pointY.clear();
	pointZ.clear();

	vec3 sizeGrid = layers[0]->GlobalSize;
	sizeGrid.y = 0;

	for (auto layer : layers) {
		pointX.push_back((layer->position.x - layer->size.x) * 2);
		pointX.push_back((layer->position.x + layer->size.x) * 2);

		pointY.push_back((layer->position.y - layer->size.y) * 2);
		pointY.push_back((layer->position.y + layer->size.y) * 2);

		pointZ.push_back((layer->position.z - layer->size.z) * 2);
		pointZ.push_back((layer->position.z + layer->size.z) * 2);
		sizeGrid.x = std::max(sizeGrid.x, layer->GlobalSize.x);
		sizeGrid.z = std::max(sizeGrid.z, layer->GlobalSize.z);
		sizeGrid.y += layer->GlobalSize.y;
	}
	for (auto cube : cubes)
	{
		pointX.push_back((cube->position.x - cube->size.x) * 2);
		pointX.push_back((cube->position.x + cube->size.x) * 2);

		pointY.push_back((cube->position.y - cube->size.y) * 2);
		pointY.push_back((cube->position.y + cube->size.y) * 2);

		pointZ.push_back((cube->position.z - cube->size.z) * 2);
		pointZ.push_back((cube->position.z + cube->size.z) * 2);
	}

	int l, r;
	int minNODX = NOD(pointX[0], pointX[1]);
	for (int i = 0; i < pointX.size(); i++)
		for (int j = 0; j < pointX.size(); j++)
			if (pointX[i] != 0 && pointX[j] != 0)
			{
				l = pointX[i];
				r = pointX[j];
				if (l < 0) {
					r -= l*2;
					l = -l;
				}
				if (r < 0) {
					l -= r*2;
					r = -r;
				}
				minNODX = std::min(minNODX, NOD(l, r));
			}

	int minNODY = NOD(pointY[0], pointY[1]);
	for (int i = 0; i < pointY.size(); i++)
		for (int j = 0; j < pointY.size(); j++)
			if (pointY[i] != 0 && pointY[j] != 0)
				{
					l = pointY[i];
					r = pointY[j];
					if (l < 0) {
						r -= l*2;
						l = -l;
					}
					if (r < 0) {
						l -= r*2;
						r = -r;
					}
					minNODY = std::min(minNODY, NOD(l, r));
				}

	int minNODZ = NOD(pointZ[0], pointZ[1]);
	for (int i = 0; i < pointZ.size(); i++)
		for (int j = 0; j < pointZ.size(); j++)
			if (pointZ[i] != 0 && pointZ[j] != 0)
				{
					l = pointZ[i];
					r = pointZ[j];
					if (l < 0) {
						r -= l*2;
						l = -l;
					}
					if (r < 0) {
						l -= r*2;
						r = -r;
					}
					minNODZ = std::min(minNODZ, NOD(l, r));
				}
	vec3 new_sizeGrid = vec3(sizeGrid.x / 2, sizeGrid.y / 2, sizeGrid.z / 2);

	grids.push_back(new Grid(layers[0]->position - layers[0]->size, sizeGrid, vec3(minNODX/2, minNODY/2, minNODZ/2)));
	
	return true;
}

Parallelepiped* getCube(ifstream* input, bool withMaterial=false)
{
	vec3 position, size;
	(*input) >> position.x >> position.y >> position.z >> size.x >> size.y >> size.z;
	int material = 0;
	if (withMaterial)
		(*input) >> material;
	return new Parallelepiped(position, size, material);
}

bool InitOther()
{
	camera = new Camera();
	
	//mesh = new Mesh("ElephantBody.3ds");
	//mesh->AddTexture("texture01.jpg", textureID1);
	//mesh->AddTexture("sun_tex.bmp", textureID1);

	ifstream input("cubes.api");
	int countLayers, countCubes;
	input >> countLayers;
	
	for (int i = 0; i < countLayers; i++)
		layers.push_back(getCube(&input));
	
	input >> countCubes;
	for (int j = 0; j < countCubes; j++)
		cubes.push_back(getCube(&input, true));

	InitGrid();
	
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

	glutInitWindowSize ( 900, 900 ) ;

	/* Create the window */
	glutCreateWindow("Bachelor Work");

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