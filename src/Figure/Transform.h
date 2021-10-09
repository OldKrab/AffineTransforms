#pragma once
#include <vector>
#include <SFML/System/Vector3.hpp>

#include "Matrix.h"

class Transform
{
public:
	Transform();
	explicit Transform(const Matrix<float>& matrix);
	const Matrix<float>& GetMatrix() const;

	void Scale(const sf::Vector3f& scale);
	void Translate(const sf::Vector3f& trans);
	void Rotate(const sf::Vector3f& angles);
	void Combine(const Transform& otherTransform);
	void ProjectOnXY();
	Transform GetCombination(const Transform& otherTransform) const;
	

private:
	static float angleProjection_;
	Matrix<float> matrix_;
};
