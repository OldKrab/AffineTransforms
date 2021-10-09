#pragma once
#include "Matrix.h"
#include "BaseFigure.h"
#include <SFML/Graphics.hpp>

class WireFigure: public BaseFigure
{
public:
	WireFigure(Matrix<float> dots);
	void SetLine(size_t firstDotIndex, size_t secondDotIndex);
	Matrix<float> dots;
	void Draw(sf::RenderTarget& target, const Transform& trans = Transform()) const override;

private:
	std::vector<std::pair<size_t, size_t>> lines_;
};

