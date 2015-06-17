#pragma once
#include "BaseObject.h"

class Interface : BaseObject
{
	GLfloat* _mapcoordList;
	GLuint uvbuffer;

protected:
	virtual void init() override;
	virtual void initCircuit() override;
	virtual void initShaders() override;
	virtual void initGeometry() override;

public:
	Interface();
	void Draw();
	~Interface();
};

