#pragma once
#include "includes.h"

using namespace glm;

class SectionSphere
{
public:
	vec3 center;
	float radius;
public:
	SectionSphere();
	float getColor(vec3 target);
	~SectionSphere();
};

