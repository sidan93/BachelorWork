#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"
#include "BaseObject.h"

using namespace glm;

class Grid : BaseObject
{
private:
	int countPoint;
protected:
	vec3 step;
	vec3 start;
	vec3 size;
protected:
	virtual void init() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;
public:
	Grid(vec3 center, vec3 size, vec3 step);
	void Draw(float *MVP);
	~Grid();
};

