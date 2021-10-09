#include "Figure.h"
#include "AffineTransforms.h"

float Figure::angleProjection = 3.1415f/4;

Figure::Figure(Matrix<float> dots) :dots(std::move(dots)) {}

void Figure::SetLine(size_t firstDotIndex, size_t secondDotIndex)
{
	lines_.emplace_back(firstDotIndex, secondDotIndex);
}

void Figure::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto newDots = AffineTransforms::Scale(dots, scale_);
	newDots = AffineTransforms::Rotate(newDots, rotate_);
	newDots = AffineTransforms::Translation(newDots, trans_);
	newDots = AffineTransforms::ProjectionOnXY(newDots, angleProjection);
	newDots = AffineTransforms::Translation(newDots, globalCenter_);
	
	std::vector<sf::Vertex> shape;
	shape.reserve(lines_.size() * 2);
	for (const auto& line : lines_)
	{
		const auto& dot1 = newDots[line.first];
		const auto& dot2 = newDots[line.second];
		shape.emplace_back(sf::Vector2f{ dot1[0] / dot1[3], (target.getSize().y - dot1[1]) / dot1[3] });
		shape.emplace_back(sf::Vector2f{ dot2[0] / dot2[3], (target.getSize().y - dot2[1])/dot2[3] });
	}
	target.draw(shape.data(), shape.size(), sf::Lines);
}
