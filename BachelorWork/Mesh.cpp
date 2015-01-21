#include "Mesh.h"


Mesh::Mesh(void)
{
	MAX_POLYGONS = 10000;
	MAX_VERTICES = 10000;
	name = "                                                     ";
}

bool Mesh::Load3D(const char * file)
{
	int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information

	if ((l_file=fopen (file, "rb"))== NULL) return false; //Open the file

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
		{
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d 
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x4d4d: 
			break;    

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info 
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
		case 0x4000: 
			i=0;
			do
			{
				fread (&l_char, 1, 1, l_file);
				name[i]=l_char;
				i++;
			}while(l_char != '\0' && i<20);
			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
		case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices) 
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
		case 0x4110: 
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			_countVectices = l_qty;
			_vertex = new vec3[_countVectices];
			printf("Number of vertices: %d\n",l_qty);
			for (i=0; i<l_qty; i++)
			{
				float x,y,z;
				fread(&_vertex[i].x, sizeof(float), 1, l_file);
				printf("Vertices list x: %f\n",_vertex[i].x);
				fread (&_vertex[i].y, sizeof(float), 1, l_file);
				printf("Vertices list y: %f\n",_vertex[i].y);
				fread (&_vertex[i].z, sizeof(float), 1, l_file);
				printf("Vertices list z: %f\n",_vertex[i].z);
			}
			break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons) 
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
		case 0x4120:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			_countPolygons = l_qty;
			_polygon = new vec3[_countPolygons];
			printf("Number of polygons: %d\n",l_qty); 
			for (i=0; i<l_qty; i++)
			{
				fread (&_polygon[i].x, sizeof (unsigned short), 1, l_file);
				printf("Polygon point a: %d\n",_polygon[i].x);
				fread (&_polygon[i].y, sizeof (unsigned short), 1, l_file);
				printf("Polygon point b: %d\n",_polygon[i].y);
				fread (&_polygon[i].z, sizeof (unsigned short), 1, l_file);
				printf("Polygon point c: %d\n",_polygon[i].z);
				fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
				printf("Face flags: %x\n",l_face_flags);
			}
			break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points) 
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
		case 0x4140:
			fread (&l_qty, sizeof (unsigned short), 1, l_file);
			_countMapcoord = l_qty;
			_mapcoord = new vec2[_countMapcoord];
			for (i=0; i<l_qty; i++)
			{
				fread (&_mapcoord[i].x, sizeof (float), 1, l_file);
				printf("Mapping list u: %f\n",_mapcoord[i].x);
				fread (&_mapcoord[i].y, sizeof (float), 1, l_file);
				printf("Mapping list v: %f\n",_mapcoord[i].y);
			}
			break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
		default:
			fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
		} 
	}
	fclose (l_file); // Closes the file stream
	return true;
}

bool Mesh::LoadTexture(const char * file)
{
	_textureID = loadBMP_custom(file);
	return true;
}


GLfloat** Mesh::getPointList() const
{
	return _vertexList;
}
GLfloat** Mesh::getMapCoordList() const
{
	return _mapcoordList;
}


GLsizeiptr Mesh::getSizePointList() const
{
	return 4 * 9 * _countPolygons;
}
GLsizeiptr Mesh::getSizeMapCoordList() const
{
	return 4 * 6 * _countPolygons;
}

// ¬ысчитываем массивы которые будут учавствовать в отрисовке
void Mesh::init()
{
	_vertexList = new GLfloat*;
	_mapcoordList = new GLfloat*;
	*_vertexList = new GLfloat[9 * _countPolygons];
	*_mapcoordList = new GLfloat[6 * _countPolygons];

	for (int i = 0; i < _countPolygons; i++)
	{
		// «аполн€ем вершинны массив
		(*_vertexList)[i*9 + 0] = _vertex[int(_polygon[i].x)].x;
		(*_vertexList)[i*9 + 1] = _vertex[int(_polygon[i].x)].y;
		(*_vertexList)[i*9 + 2] = _vertex[int(_polygon[i].x)].z;

		(*_vertexList)[i*9 + 3] = _vertex[int(_polygon[i].y)].x;
		(*_vertexList)[i*9 + 4] = _vertex[int(_polygon[i].y)].y;
		(*_vertexList)[i*9 + 5] = _vertex[int(_polygon[i].y)].z;

		(*_vertexList)[i*9 + 6] = _vertex[int(_polygon[i].z)].x;
		(*_vertexList)[i*9 + 7] = _vertex[int(_polygon[i].z)].y;
		(*_vertexList)[i*9 + 8] = _vertex[int(_polygon[i].z)].z;

		// «аполн€ем текстурный массив
		(*_mapcoordList)[i*6 + 0] = _mapcoord[int(_polygon[i].x)].x;
		(*_mapcoordList)[i*6 + 1] = _mapcoord[int(_polygon[i].x)].y;

		(*_mapcoordList)[i*6 + 2] = _mapcoord[int(_polygon[i].y)].x;
		(*_mapcoordList)[i*6 + 3] = _mapcoord[int(_polygon[i].y)].y;

		(*_mapcoordList)[i*6 + 4] = _mapcoord[int(_polygon[i].z)].x;
		(*_mapcoordList)[i*6 + 5] = _mapcoord[int(_polygon[i].z)].y;
	}
	if (true)
	{
		delete[] *_vertexList;
		delete[] *_mapcoordList;

		*_vertexList = new GLfloat[_countVectices * 3];
		*_mapcoordList = new GLfloat[_countMapcoord * 3];

		for (int i = 0; i < _countVectices; i++)
		{
			(*_vertexList)[i + 0] = _vertex[i].x;
			(*_vertexList)[i + 1] = _vertex[i].y;
			(*_vertexList)[i + 2] = _vertex[i].z;
		}
		for (int i = 0; i < _countMapcoord; i++)
		{
			(*_mapcoordList)[i + 0] = _mapcoord[i].x;
			(*_mapcoordList)[i + 1] = _mapcoord[i].y;
		}
	}
}


int Mesh::CountVertex() const
{
	return 9 * _countPolygons;
}
int Mesh::CountMapcoord() const
{
	return 6 * _countPolygons;
}
Mesh::~Mesh(void)
{
}
