#pragma once
#include "Matrix.h"
#include <SFML/Graphics.hpp>

class AffineTransforms
{
public:
	static Matrix<float>  Translation(const Matrix<float>& dots, sf::Vector3f tr);
	static Matrix<float>  Scale(const Matrix<float>& dots, sf::Vector3f sc);
	static Matrix<float>  Rotate(const Matrix<float>& dots, sf::Vector3f rt);
	static Matrix<float>  ProjectionOnXY(const Matrix<float>& dots, float angle);
};
