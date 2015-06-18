#pragma once
#include "includes.h"

using namespace glm;

typedef pair<float, vec3> Coloring;

class SectionSphere
{
public:
	vec3 center;
	float radius;

	float minPower;
	float maxPower;
	vector<Coloring> coloring;
private:
	//bool SortColoring(Coloring first, Coloring second);
public:
	SectionSphere();
	vec3 getColor(vec3 target);
	void readColoring();
	~SectionSphere();
};

