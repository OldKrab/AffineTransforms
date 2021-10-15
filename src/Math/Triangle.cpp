#include "Triangle.h"

Triangle::Triangle(sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f p3) :p1(p1), p2(p2), p3(p3) {
}

Plane Triangle::CalcPlane() const
{
	if (!isCalcPlane) {
		sf::Vector3f v = p2 - p1, w = p3 - p1;
		plane.a = v.y * w.z - v.z * w.y;
		plane.b = -v.x * w.z + v.z * w.x;
		plane.c = v.x * w.y - v.y * w.x;
		plane.d = plane.a * (-p1.x) + plane.b * (-p1.y) + plane.c * (-p1.z);
		isCalcPlane = true;
	}
	return plane;
}

sf::Rect<float> Triangle::GetRect() const
{
	if (!isCalcRect)
	{
		rect.left = std::min(std::min(p1.x, p2.x), p3.x);
		rect.width = std::max(std::max(p1.x, p2.x), p3.x) - rect.left;
		rect.top = std::min(std::min(p1.y, p2.y), p3.y);
		rect.height = std::max(std::max(p1.y, p2.y), p3.y) - rect.top;
		isCalcRect = true;
	}
	return rect;
}
