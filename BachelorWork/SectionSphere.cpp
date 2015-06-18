#include "SectionSphere.h"


SectionSphere::SectionSphere()
{
}

vec3 SectionSphere::getColor(vec3 target)
{
	float range = glm::distance(target, center);
	float power = (maxPower - minPower) * (range / radius);

	if (power < coloring[0].first)
		return coloring[0].second;
	
	if (power > coloring[coloring.size() - 1].first)
		return coloring[coloring.size() - 1].second;

	int index = 0;	
	for (int i = 0; i < coloring.size(); i++) {
		if (power < coloring[i].first)
		{
			index = i - 1;
			break;
		}
	}

	float lengthWeight = coloring[index + 1].first - coloring[index].first;
	float leftWeight = (power - coloring[index].first) / lengthWeight;
	float rightWeight = (coloring[index + 1].first - power) / lengthWeight;
	
	float r = coloring[index].second.r * leftWeight + coloring[index + 1].second.r + rightWeight;
	float g = coloring[index].second.g * leftWeight + coloring[index + 1].second.g + rightWeight;
	float b = coloring[index].second.b * leftWeight + coloring[index + 1].second.b + rightWeight;
	return vec3(r, g, b);
}

bool SortColoring(Coloring first, Coloring second)
{
	if (first.first < second.first)
		return true;
	return false;
}


void SectionSphere::readColoring()
{
	ifstream file("coloring.api");
	float power;
	float r, g, b;

	do {
		file >> power >> r >> g >> b;
		coloring.push_back(Coloring(power, vec3(r, b, g)));
	} while (!file.eof());
	
	sort(coloring.begin(), coloring.end(), SortColoring);
}

SectionSphere::~SectionSphere()
{
}
