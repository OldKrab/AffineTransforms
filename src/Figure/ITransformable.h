#pragma once
#include "Transform.h"

class ITransformable
{
public:
	ITransformable();
	const Transform& GetTransform() const;

	const sf::Vector3f& GetScale() const;

	
	void Scale(const sf::Vector3f& scale);
	void Translate(const sf::Vector3f& translation);
	void Rotate(const sf::Vector3f& rotation);
	void ResetTransform() const;
private:
	sf::Vector3f scale_, translation_, rotation_;
	mutable Transform transform_;
	mutable bool transformNeedUpdate_ = false;
};
