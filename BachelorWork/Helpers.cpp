#include "Helpers.h"

string loadFile(const char *fname)
{
	ifstream file(fname);
	if(!file.is_open())
	{
		cout << "Unable to open file " << fname << endl;
		exit(1);
	}

	stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}


// Display (hopefully) useful error messages if shader fails to compile
void printShaderInfoLog(GLint shader)
{
	int infoLogLen = 0;
	int charsWritten = 0;
	GLchar *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);

	if (infoLogLen > 0)
	{
		infoLog = new GLchar[infoLogLen];
		// error check for fail to allocate memory omitted
		glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
		cout << "InfoLog : " << endl << infoLog << endl;
		delete [] infoLog;
	}
}


int LoadShader(const char *pfilePath_vs, 
			   const char *pfilePath_fs, 
			   bool bindTexCoord0, 
			   bool bindNormal, 
			   bool bindColor, 
			   GLuint &shaderProgram, 
			   GLuint &vertexShader, 
			   GLuint &fragmentShader)
{
	shaderProgram=0;
	vertexShader=0;
	fragmentShader=0;

	// load shaders & get length of each
	int vlen;
	int flen;
	string vertexShaderString = loadFile(pfilePath_vs);
	string fragmentShaderString = loadFile(pfilePath_fs);
	vlen = vertexShaderString.length();
	flen = fragmentShaderString.length();

	if(vertexShaderString.empty())
	{
		return -1;
	}

	if(fragmentShaderString.empty())
	{
		return -1;
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	

	const char *vertexShaderCStr = vertexShaderString.c_str();
	const char *fragmentShaderCStr = fragmentShaderString.c_str();
	glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlen);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flen);

	GLint compiled;

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
	if(compiled==FALSE)
	{
		cout << "Vertex shader not compiled." << endl;
		printShaderInfoLog(vertexShader);

		glDeleteShader(vertexShader);
		vertexShader=0;
		glDeleteShader(fragmentShader);
		fragmentShader=0;

		return -1;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
	if(compiled==FALSE)
	{
		cout << "Fragment shader not compiled." << endl;
		printShaderInfoLog(fragmentShader);

		glDeleteShader(vertexShader);
		vertexShader=0;
		glDeleteShader(fragmentShader);
		fragmentShader=0;

		return -1;
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "InVertex");

	if(bindTexCoord0)
		glBindAttribLocation(shaderProgram, 1, "InTexCoord0");

	if(bindNormal)
		glBindAttribLocation(shaderProgram, 2, "InNormal");

	if(bindColor)
		glBindAttribLocation(shaderProgram, 3, "InColor");

	glLinkProgram(shaderProgram);

	GLint IsLinked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (GLint *)&IsLinked);
	if(IsLinked==FALSE)
	{
		cout << "Failed to link shader." << endl;

		GLint maxLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);
		if(maxLength>0)
		{
			char *pLinkInfoLog = new char[maxLength];
			glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, pLinkInfoLog);
			cout << pLinkInfoLog << endl;
			delete [] pLinkInfoLog;
		}

		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		vertexShader=0;
		glDeleteShader(fragmentShader);
		fragmentShader=0;
		glDeleteProgram(shaderProgram);
		shaderProgram=0;

		return -1;
	}

	return 1;		//Success
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

	// Создаем шейдеры
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Загружаем код Вершинного Шейдера из файла
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Загружаем код Фрагментного шейдера из файла
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Компилируем Вершинный шейдер
	printf("Compile Vertex shader: %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Выполняем проверку Вершинного шейдера
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Компилируем Фрагментный шейдер
	printf("Compile Fragment Shader: %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Проверяем Фрагментный шейдер
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Создаем шейдерную программу и привязываем шейдеры к ней
	fprintf(stdout, "Create shader program \n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Проверяем шейдерную программу
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}