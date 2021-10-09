#include "ITransformable.h"

ITransformable::ITransformable():translation_{0,0,0}, scale_{1,1,1}, rotation_{0,0,0}{}

const Transform& ITransformable::GetTransform() const
{
	if (transformNeedUpdate_)
	{
		ResetTransform();
		transform_.Scale(scale_);
		transform_.Rotate(rotation_);
		transform_.Translate(translation_);
		transformNeedUpdate_ = false;
	}
	return transform_;
}

const sf::Vector3f& ITransformable::GetScale() const
{
	return scale_;
}

void ITransformable::Scale(const sf::Vector3f& scale)
{
	scale_ += scale;
	transformNeedUpdate_ = true;
}

void ITransformable::Translate(const sf::Vector3f& translation)
{
	translation_ += translation;
	transformNeedUpdate_ = true;
}

void ITransformable::Rotate(const sf::Vector3f& rotation)
{
	rotation_ += rotation;
	transformNeedUpdate_ = true;
}

void ITransformable::ResetTransform() const
{
	transform_ = Transform();
}
