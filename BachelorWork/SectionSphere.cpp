#include "SectionSphere.h"


SectionSphere::SectionSphere()
{
}

float SectionSphere::getColor(vec3 target)
{
	float range = glm::distance(target, center);
	float color = range / radius;
	return color;
}

SectionSphere::~SectionSphere()
{
}
