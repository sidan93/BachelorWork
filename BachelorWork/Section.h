#pragma once
#include "BaseObject.h"
#include "includes.h"

using namespace glm;

class Section : public BaseObject
{
	vec3 position;
	vec3 direction;
	vec3 maxSize;
	int step;

	int countPoint;
protected:
	virtual void init() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;
	virtual void initCircuit() override;
public:
	Section();
	
	void Init();

	void Draw(float *MVP);
	void Update();

	vec3 getPosition() const;
	void setMaxSize(vec3 size_);

	~Section();
};

