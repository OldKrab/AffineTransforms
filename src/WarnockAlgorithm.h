#pragma once
#include <stack>
#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Math/Triangle.h"

class WarnockAlgorithm
{
public:
	WarnockAlgorithm(const std::vector<Triangle>& triangles, const std::vector<sf::Color>& colors);
	void Run(sf::RenderTarget& target);
	void StepRun(sf::RenderWindow& window);
	void Step(const sf::Rect<int>& rect);

	const float MIN_Z = -1e5;
private:
	static bool IsTriangleOutsideRect(const sf::Rect<int>& rect, const Triangle& triangle);
	static bool IsPointInTriangle2d(sf::Vector2f point, const Triangle& triangle);
	static bool IsRectsIntersect(const sf::Rect<int>& r1, const sf::Rect<int>& r2);
	static float GetZ(sf::Vector2f p, const Triangle& triangle);
	static std::vector<sf::Rect<int>> SplitRect(const sf::Rect<int>& rect);
	
	 void DrawStack(sf::RenderWindow& window);
	 void DrawRect(sf::RenderWindow& window, const sf::Rect<int>& r);
	
	const std::vector<Triangle>& triangles;
	const std::vector<sf::Color>& colors;
	
	std::stack<sf::Rect<int>> rectStack;
	std::vector<sf::Vertex> drawPoints;
	sf::VertexArray drawTriangles{ sf::Triangles };
};
