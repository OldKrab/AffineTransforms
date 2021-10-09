#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include "Transform.h"

class IDrawable
{
public:
	virtual void Draw(sf::RenderTarget& target, const Transform& trans) const = 0;
	virtual ~IDrawable() = default;
};
