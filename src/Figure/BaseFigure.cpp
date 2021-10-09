#include "BaseFigure.h"
#include "AffineTransforms.h"

BaseFigure::BaseFigure() :trans_(0, 0, 0), scale_(1, 1, 1), rotate_(0, 0, 0) {}


sf::Vector3f BaseFigure::GetScale() const
{
	return scale_;
}


void BaseFigure::SetGlobalCenter(sf::Vector3f crd)
{
	globalCenter_ = crd;
}


void BaseFigure::AddScale(sf::Vector3f scale)
{
	scale_ += scale;
}

void BaseFigure::AddTranslation(sf::Vector3f trans)
{
	trans_ += trans;
}

void BaseFigure::AddRotate(sf::Vector3f rot)
{
	rotate_ += rot;
	auto tr = AffineTransforms::Rotate(Matrix<float>({ {trans_.x, trans_.y, trans_.z, 1} }), rot);
	trans_ = sf::Vector3f{ tr[0][0], tr[0][1], tr[0][2] };
}


void BaseFigure::ResetTransform()
{
	trans_ = {0, 0, 0};
	scale_ = {1, 1, 1};
	rotate_ = {0,0,0};
}