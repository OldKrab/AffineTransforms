#include "WireFigure.h"
#include "AffineTransforms.h"


WireFigure::WireFigure() :WireFigure(Matrix<float>()) {}

WireFigure::WireFigure(Matrix<float> dots) : dots_(std::move(dots)) {}

void WireFigure::SetLine(size_t firstDotIndex, size_t secondDotIndex)
{
	lines_.emplace_back(firstDotIndex, secondDotIndex);
}

void WireFigure::Draw(sf::RenderTarget& target, const Transform& trans) const
{
	auto resTransform = GetTransform().GetCombination(trans);
	auto newDots = dots_ * resTransform.GetMatrix();
	std::vector<sf::Vertex> shape;
	shape.reserve(lines_.size() * 2);
	for (const auto& line : lines_)
	{
		const auto& dot1 = newDots[line.first];
		const auto& dot2 = newDots[line.second];
		shape.emplace_back(sf::Vector2f{ dot1[0] / dot1[3], (dot1[1]) / dot1[3] });
		shape.emplace_back(sf::Vector2f{ dot2[0] / dot2[3], (dot2[1]) / dot2[3] });
	}
	target.draw(shape.data(), shape.size(), sf::Lines);
}
