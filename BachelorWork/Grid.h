#pragma once
#include "includes.h"
#include "Helpers.h"
#include "Texture.h"
#include "BaseObject.h"
#include "Section.h"

using namespace glm;

class Grid : public BaseObject
{
private:
	int countPoint;
	float alpha;
	int alphaID;
	int cameraPositionID;

	Section *section;
protected:
	vec3 step;
	vec3 start;
	vec3 size;
protected:
	virtual void init() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;
	virtual void initCircuit() override;
public:
	Grid(vec3 center, vec3 size, vec3 step);
	void setAlpha(float value);
	void Draw(float *MVP, vec3 cameraPosition);
	vec3 getCenter() const;

	void setSectionLink(Section *section);

	~Grid();
};

