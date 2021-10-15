#include "VectorHelper.h"


sf::Vector3f VectorHelper::GetVector3fFromFourCrds(const std::vector<float>& v)
{
	return { v[0] / v[3], v[1] / v[3], v[2] / v[3] };
}

sf::Vector3f VectorHelper::Normalize(const sf::Vector3f& v)
{
	return v / Length(v);
}

float VectorHelper::Length(const sf::Vector3f& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float VectorHelper::DotProd(const sf::Vector3f& v, const sf::Vector3f& w)
{
	return v.x* w.x + v.y * w.y + v.z * w.z;
}

float VectorHelper::CrossProd(const sf::Vector2f& v, const sf::Vector2f& w)
{
	return v.x* w.y - v.y * w.x;
}
