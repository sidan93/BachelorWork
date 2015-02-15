#include "Texture.h"


Texture::Texture(const char *filename) : Texture(filename, -1)
{
}

Texture::Texture(const char *filename, GLuint shaderIndex) 
	: _filename(filename), _shaderIndex(shaderIndex)
{
	_id = loadTexture();
}

void Texture::BindTexture(GLuint shaderIndex, int textureNumber) {
	glUniform1i(shaderIndex, textureNumber);
	glActiveTexture(GL_TEXTURE0 + textureNumber);
	glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::BindTexture(int textureNumber) {
	return BindTexture(_shaderIndex, textureNumber);
}

GLuint Texture::loadTexture()
{
	FIBITMAP *dib1 = NULL;

	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(_filename);

	dib1 = FreeImage_Load(fif, _filename, JPEG_DEFAULT);
	if (!dib1)
	{
		std::cerr << "Erreur ouverture d\'image" << std::endl;
		exit(0);

	}

	GLuint tex_id = 0;
	int x, y;
	int height, width;

	RGBQUAD rgbquad;


	FREE_IMAGE_TYPE type;
	BITMAPINFOHEADER *header;

	type = FreeImage_GetImageType(dib1);


	height = FreeImage_GetHeight(dib1);
	width = FreeImage_GetWidth(dib1);

	header = FreeImage_GetInfoHeader(dib1);
	int scanLineWidh = ((3 * width) % 4 == 0) ? 3 * width : ((3 * width) / 4) * 4 + 4;
	unsigned char * texels = (GLubyte*)calloc(height*scanLineWidh, sizeof(GLubyte));
	for (x = 0; x<width; x++)
		for (y = 0; y<height; y++)
		{
			FreeImage_GetPixelColor(dib1, x, y, &rgbquad);

			texels[(y*scanLineWidh + 3 * x)] = ((GLubyte*)&rgbquad)[2];
			texels[(y*scanLineWidh + 3 * x) + 1] = ((GLubyte*)&rgbquad)[1];
			texels[(y*scanLineWidh + 3 * x) + 2] = ((GLubyte*)&rgbquad)[0];
		}

	glGenTextures(1, &tex_id);
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, texels);
	free(texels);

	return tex_id;
}

Texture::~Texture()
{
}
