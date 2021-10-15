#pragma once
#include <SFML/System/Vector3.hpp>

struct Plane
{
	Plane(float a, float b, float c, float d);
	Plane();
	sf::Vector3f GetNorm() const;
	float GetZ(float x, float y) const;
 	float a, b, c, d;
};
