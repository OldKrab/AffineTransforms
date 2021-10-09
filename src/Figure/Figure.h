#pragma once
#include "Matrix.h"
#include "BaseFigure.h"
#include <SFML/Graphics.hpp>

class Figure: public BaseFigure
{
public:
	Figure(Matrix<float> dots);
	void SetLine(size_t firstDotIndex, size_t secondDotIndex);
	Matrix<float> dots;
	static float angleProjection;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<std::pair<size_t, size_t>> lines_;
};

