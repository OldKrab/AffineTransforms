#include "ITransformable.h"

ITransformable::ITransformable() :translation_{ 0,0,0 }, scale_{ 1,1,1 }, rotation_{ 0,0,0 }{}

const Transform& ITransformable::GetTransform() const
{
	if (transformNeedUpdate_)
	{
		ClearTransformMatrix();
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

void ITransformable::SetScale(const sf::Vector3f& scale)
{
	scale_ = scale;
	transformNeedUpdate_ = true;
}

void ITransformable::SetTranslation(const sf::Vector3f& translation)
{
	translation_ = translation;
	transformNeedUpdate_ = true;

}

void ITransformable::SetRotation(const sf::Vector3f& rotation)
{
	rotation_ = rotation;
	transformNeedUpdate_ = true;
}

void ITransformable::Scale(const sf::Vector3f& scale)
{
	SetScale(scale_ + scale);
}

void ITransformable::Translate(const sf::Vector3f& translation)
{
	SetTranslation(translation_ + translation);
}

void ITransformable::Rotate(const sf::Vector3f& rotation)
{
	SetRotation(rotation_ +rotation);
}

void ITransformable::ResetTransform()
{
	ClearTransformMatrix();
	translation_ = { 0,0,0 };
	scale_ = { 1,1,1 };
	rotation_ = { 0,0,0 };
}

void ITransformable::ClearTransformMatrix() const
{
	transform_ = Transform();
}
