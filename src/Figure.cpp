#include "Figure.h"
#include "AffineTransforms.h"
#include <math.h>

float Figure::angleProjection = 3.1415f/4;


Figure::Figure(Matrix<float> dots) :dots(std::move(dots)), trans_(0, 0, 0), scale_(1, 1, 1), rotate_(0,0,0) {}

void Figure::SetLine(size_t firstDotIndex, size_t secondDotIndex)
{
	lines_.emplace_back(firstDotIndex, secondDotIndex);
}

sf::Vector3f Figure::GetScale() const
{
	return scale_;
}

void Figure::AddScale(sf::Vector3f scale)
{
	scale_ += scale;
}


void Figure::AddTranslation(sf::Vector3f trans)
{
	trans_ += trans;
}

void Figure::AddRotate(sf::Vector3f rot)
{
	rotate_ += rot;
	auto tr = AffineTransforms::Rotate(Matrix<float>({{trans_.x, trans_.y, trans_.z, 1}}), rot);
	trans_ = sf::Vector3f{tr[0][0], tr[0][1], tr[0][2]};
}

void Figure::SetGlobalCenter(sf::Vector3f crd)
{
	globalCenter_ = crd;
}

void Figure::ResetTransform()
{
	trans_ = {0, 0, 0};
	scale_ = {1, 1, 1};
	rotate_ = {0,0,0};
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
		shape.emplace_back(sf::Vector2f{ dot2[0], target.getSize().y - dot2[1] });
	}
	target.draw(shape.data(), shape.size(), sf::Lines);
}
