#include "Transform.h"

#include "AffineTransforms.h"

float Transform::angleProjection_ = 3.1415f / 4;

Transform::Transform() :matrix_{ { {1,0,0,0}, {0,1,0,0},{0,0,1,0}, {0,0,0,1}} } {}

Transform::Transform(const Matrix<float>& matrix):matrix_(matrix){}

const Matrix<float>& Transform::GetMatrix() const
{
	return matrix_;
}


void Transform::Scale(const sf::Vector3f& scale)
{
	matrix_ = AffineTransforms::Scale(matrix_, scale);
}

void Transform::Translate(const sf::Vector3f& trans)
{
	matrix_ = AffineTransforms::Translate(matrix_, trans);
}

void Transform::Rotate(const sf::Vector3f& angles)
{
	matrix_ = AffineTransforms::Rotate(matrix_, angles);
}

void Transform::Combine(const Transform& otherTransform)
{
	matrix_ = GetCombination(otherTransform).GetMatrix();
}

void Transform::ProjectOnXY()
{
	matrix_ = AffineTransforms::ProjectionOnXY(matrix_, angleProjection_);
}

Transform Transform::GetCombination(const Transform& otherTransform) const
{
	return Transform(matrix_ * otherTransform.matrix_);
}


