#pragma once
#include "Transform.h"

class ITransformable
{
public:
	ITransformable();
	const Transform& GetTransform() const;

	const sf::Vector3f& GetScale() const;

		void SetScale(const sf::Vector3f& scale);
	void SetTranslation(const sf::Vector3f& translation);
	void SetRotation(const sf::Vector3f& rotation);
	
	void Scale(const sf::Vector3f& scale);
	void Translate(const sf::Vector3f& translation);
	void Rotate(const sf::Vector3f& rotation);
	void ResetTransform();
private:
	void ClearTransformMatrix() const;
	sf::Vector3f scale_, translation_, rotation_;
	mutable Transform transform_;
	mutable bool transformNeedUpdate_ = false;
};
