#include "Mesh.h"


Mesh::Mesh(const char *meshFile)
{
	name = "                                                     ";

	_countVectices = vector<int>();
	_countPolygons = vector<int>();
	_countMapcoord = vector<int>();

	_vertex = vector<vertex_type*>();
	_polygon = vector<polygon_type*>();
	_mapcoord = vector<mapcoord_type*>();

	_drawType = GL_POINTS;
	
	Load3D(meshFile);
	init();
	initGeometry();

}

void Mesh::AddTexture(const char *textureFile, GLuint shaderTextureId) {
	auto cash = _texture.find(textureFile);
	if (cash == _texture.end())
		_texture[textureFile] = new Texture(textureFile, shaderTextureId);
}

bool Mesh::Load3D(const char * file)
{
	int i; //Index variable
	int position;
	unsigned short value;
	int z = 0;

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
		//printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		//printf("ChunkLenght: %x\n",l_chunk_lenght);

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
			_countVectices.push_back(l_qty);
			position = _vertex.size();
			_vertex.push_back(new vertex_type[l_qty]);
			printf("Number of vertices: %d\n",l_qty);
			for (i=0; i<l_qty; i++)
			{
				_vertex[position][i].x = 0;
				_vertex[position][i].y = 0;
				_vertex[position][i].z = 0;
				fread(&_vertex[position][i].x, sizeof(float), 1, l_file);
				//printf("Vertices list x: %f\n",_vertex[i].x);
				fread (&_vertex[position][i].y, sizeof(float), 1, l_file);
				//printf("Vertices list y: %f\n",_vertex[i].y);
				fread (&_vertex[position][i].z, sizeof(float), 1, l_file);
				//printf("Vertices list z: %f\n",_vertex[i].z);
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
			_countPolygons.push_back(l_qty);
			position = _polygon.size();
			_polygon.push_back(new polygon_type[l_qty]);
			printf("Number of polygons: %d\n",l_qty); 
			for (i=0; i<l_qty; i++)
			{
				_polygon[position][i].a = 0;
				_polygon[position][i].b = 0;
				_polygon[position][i].c = 0;
				int value;
				fread (&_polygon[position][i].a, sizeof (unsigned short), 1, l_file);
				//printf("Polygon point a: %d\n",_polygon[i].x);
				fread (&_polygon[position][i].b, sizeof (unsigned short), 1, l_file);
				//printf("Polygon point b: %d\n",_polygon[i].y);
				fread (&_polygon[position][i].c, sizeof (unsigned short), 1, l_file);
				//printf("Polygon point c: %d\n",_polygon[i].z);
				fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
				//printf("Face flags: %x\n",l_face_flags);
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
			_countMapcoord.push_back(l_qty);
			position = _mapcoord.size();
			_mapcoord.push_back(new mapcoord_type[l_qty]);
			for (i=0; i<l_qty; i++)
			{
				_mapcoord[position][i].u = 0;
				_mapcoord[position][i].v = 0;
				fread (&_mapcoord[position][i].u, sizeof (float), 1, l_file);
				//printf("Mapping list u: %f\n",_mapcoord[i].x);
				fread (&_mapcoord[position][i].v, sizeof (float), 1, l_file);
				//printf("Mapping list v: %f\n",_mapcoord[i].y);
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


// Высчитываем массивы которые будут учавствовать в отрисовке
void Mesh::init()
{
	_vertexList = vector<GLfloat*>();
	_mapcoordList = vector<GLfloat*>();
	_normalList = vector<GLfloat*>();

	_countVertexList = vector<int>();
	_countMapcoordList = vector<int>();
	_countNormalList = vector<int>();

	for (int position = 0; position < _countPolygons.size(); position++)
	{
		_vertexList.push_back(new GLfloat[_countPolygons[position] * 9]);
		_mapcoordList.push_back(new GLfloat[_countPolygons[position] * 6]);
		_normalList.push_back(new GLfloat[_countPolygons[position] *3]);
		
		for (int i = 0; i < _countPolygons[position]; i++)
		{
			// Заполняем вершинны массив
			_vertexList[position][i*9 + 0] = _vertex[position][_polygon[position][i].a].x;
			_vertexList[position][i*9 + 1] = _vertex[position][_polygon[position][i].a].y;
			_vertexList[position][i*9 + 2] = _vertex[position][_polygon[position][i].a].z;

			_vertexList[position][i*9 + 3] = _vertex[position][_polygon[position][i].b].x;
			_vertexList[position][i*9 + 4] = _vertex[position][_polygon[position][i].b].y;
			_vertexList[position][i*9 + 5] = _vertex[position][_polygon[position][i].b].z;

			_vertexList[position][i*9 + 6] = _vertex[position][_polygon[position][i].c].x;
			_vertexList[position][i*9 + 7] = _vertex[position][_polygon[position][i].c].y;
			_vertexList[position][i*9 + 8] = _vertex[position][_polygon[position][i].c].z;
			
			// Расчитаем нормаль к тругольнику
			vec3 v1 = vec3(_vertexList[position][i*9 + 0], _vertexList[position][i*9 + 1], _vertexList[position][i*9 + 2]);
			vec3 v2 = vec3(_vertexList[position][i*9 + 3], _vertexList[position][i*9 + 4], _vertexList[position][i*9 + 5]);
			vec3 v3 = vec3(_vertexList[position][i*9 + 6], _vertexList[position][i*9 + 7], _vertexList[position][i*9 + 8]);

			vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
			_normalList[position][i*3 + 0] = normal.x;
			_normalList[position][i*3 + 1] = normal.y;
			_normalList[position][i*3 + 2] = normal.z;

			if (_countMapcoord.size() > position && _countMapcoord[position] != 0) 
			{
				// Заполняем текстурный массив
				_mapcoordList[position][i*6 + 0] = _mapcoord[position][_polygon[position][i].a].u;
				_mapcoordList[position][i*6 + 1] = _mapcoord[position][_polygon[position][i].a].v;

				_mapcoordList[position][i*6 + 2] = _mapcoord[position][_polygon[position][i].b].u;
				_mapcoordList[position][i*6 + 3] = _mapcoord[position][_polygon[position][i].b].v;

				_mapcoordList[position][i*6 + 4] = _mapcoord[position][_polygon[position][i].c].u;
				_mapcoordList[position][i*6 + 5] = _mapcoord[position][_polygon[position][i].c].v;
			}
		}
	}
}

void Mesh::initGeometry()
{
	// Магия без которой не рисует
	glGenVertexArrays(1, &vertexArrays);
	glBindVertexArray(vertexArrays);
	vertexbuffer.resize(_countPolygons.size());
	uvbuffer.resize(_countPolygons.size());
	normalbuffer.resize(_countPolygons.size());

	for (int i = 0; i < _countPolygons.size(); i++)
	{
		glGenBuffers(1, &vertexbuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, _countPolygons[i] * 4 * 9, _vertexList[i], GL_STATIC_DRAW);

		glGenBuffers(1, &uvbuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, _countPolygons[i] * 4 * 6, _mapcoordList[i], GL_STATIC_DRAW);

		glGenBuffers(1, &normalbuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, _countPolygons[i] * 4 * 3, _normalList[i], GL_STATIC_DRAW);
	}
}
void Mesh::Draw() 
{
	int index = 0;
	map<const char*, Texture*>::iterator item;
	for (item = _texture.begin(), index; item != _texture.end(); item++, index++)
		item->second->BindTexture(index);

	for (int i = 0; i < _countPolygons.size(); i++)
	{

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);
		glVertexAttribPointer(
			0,                 
			3,                 
			GL_FLOAT,          
			GL_FALSE,          
			0,                 
			(void*)0           
		);

		// 2nd attribute buffer : uv
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer[i]);
		glVertexAttribPointer(
			1,                            
			2,                             
			GL_FLOAT,                      
			GL_FALSE,                      
			0,                             
			(void*)0                       
		);

		// 3nd attribute buffer : normal
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[i]);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);


		// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, object.polygons_qty * 3); 

		glDrawArrays(_drawType, 0, _countPolygons[i] * 9 * 4); 

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

void Mesh::setDrawType(int type)
{
	_drawType = type;
}

Mesh::~Mesh(void)
{
}
