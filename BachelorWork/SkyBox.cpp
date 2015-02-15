#include "SkyBox.h"


SkyBox::SkyBox()
{

}

SkyBox::SkyBox(const char * file)
{
	texture = loadTexture(file);
}


SkyBox::~SkyBox(void)
{
}
