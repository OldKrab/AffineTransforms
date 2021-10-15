#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector3.hpp>

#include "Plane.h"

struct Triangle
{
	Triangle(sf::Vector3f p1, sf::Vector3f p2, sf::Vector3f p3);
	Plane CalcPlane() const;
	sf::Rect<float> GetRect() const;
	
	sf::Vector3f p1, p2, p3;
private:
	mutable sf::Rect<float> rect;
	mutable bool isCalcRect = false;
	mutable Plane plane;
	mutable bool isCalcPlane = false;
};
