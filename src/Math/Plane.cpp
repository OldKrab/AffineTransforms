#include "Plane.h"

Plane::Plane(float a, float b, float c, float d):a(a), b(b), c(c), d(d) {}

Plane::Plane():Plane(0,0,0,0){}

sf::Vector3f Plane::GetNorm() const
{
	return {a,b,c};
}

float Plane::GetZ(float x, float y) const
{
	return -(a*x + b*y + d) / c;
}
