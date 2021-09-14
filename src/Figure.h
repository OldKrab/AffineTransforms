#pragma once
#include "Matrix.h"
#include <SFML/Graphics.hpp>

class Figure:public sf::Drawable
{
public:
	Figure(Matrix<float> dots);
	void SetLine(size_t firstDotIndex, size_t secondDotIndex);
	sf::Vector3f GetScale() const;
	void AddScale(sf::Vector3f scale);
	void AddTranslation(sf::Vector3f trans);
	void AddRotate(sf::Vector3f rot);
	void SetGlobalCenter(sf::Vector3f crd);
	void ResetTransform();
	Matrix<float> dots;
	static float angleProjection;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector3f trans_, scale_, rotate_, globalCenter_;
	std::vector<std::pair<size_t, size_t>> lines_;
};

