#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

class VectorHelper
{
public:
	static sf::Vector3f GetVector3fFromFourCrds(const std::vector<float>& v);
	static sf::Vector3f Normalize(const sf::Vector3f& v);
	static float Length(const sf::Vector3f& v);
	static float DotProd(const sf::Vector3f& v, const sf::Vector3f& w);
	static float CrossProd(const sf::Vector2f& v, const sf::Vector2f& w);
};
