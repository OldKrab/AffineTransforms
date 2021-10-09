#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector3.hpp>

class BaseFigure :public sf::Drawable
{
public:
	sf::Vector3f GetScale() const;
	
	virtual void AddScale(sf::Vector3f scale);
	virtual void AddTranslation(sf::Vector3f trans);
	virtual void AddRotate(sf::Vector3f rot);

	void SetGlobalCenter(sf::Vector3f crd);
	
	void ResetTransform();

protected:
	BaseFigure();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	
	sf::Vector3f trans_, scale_, rotate_, globalCenter_;
};

