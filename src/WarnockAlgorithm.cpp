#include "WarnockAlgorithm.h"

#include <stack>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Math/VectorHelper.h"


WarnockAlgorithm::WarnockAlgorithm(const std::vector<Triangle>& triangles, const std::vector<sf::Color>& colors) :triangles(triangles), colors(colors) {}

void WarnockAlgorithm::Run(sf::RenderTarget& target)
{
	drawPoints.reserve(50000);
	rectStack.push({ {0,0}, static_cast<sf::Vector2i>(target.getSize()) });
	sf::RenderWindow* window = (sf::RenderWindow*)&target;
	while (!rectStack.empty())
	{
		const auto& rect = rectStack.top();
		rectStack.pop();
		Step(rect);
	}
	target.draw(drawPoints.data(), drawPoints.size(), sf::Points);
}

void WarnockAlgorithm::StepRun(sf::RenderWindow& window)
{
	drawPoints.reserve(50000);
	rectStack.push({ {0,0}, static_cast<sf::Vector2i>(window.getSize()) });
	while (!rectStack.empty())
	{
		window.clear();
		DrawStack(window);
		const auto& rect = rectStack.top();
		rectStack.pop();
		Step(rect);
		window.draw(drawPoints.data(), drawPoints.size(), sf::Points);
		window.display();
	}
}

void WarnockAlgorithm::Step(const sf::Rect<int>& rect)
{
	std::vector<char> isOutside(triangles.size());
	bool isAllOutside = true;
	for (size_t i = 0; i < triangles.size(); i++) {
		isOutside[i] = IsTriangleOutsideRect(rect, triangles[i]);
		if (!isOutside[i])
			isAllOutside = false;
	}
	if (!isAllOutside)
	{
		if (rect.height == 1 && rect.width == 1) {
			sf::Vector2f point(rect.left, rect.top);
			float maxZ = MIN_Z;
			size_t maxZInx = 0;
			for (size_t i = 0; i < triangles.size(); i++)
				if (!isOutside[i] && IsPointInTriangle2d(point, triangles[i]))
				{
					float z = GetZ(point, triangles[i]);
					if (z > maxZ)
					{
						maxZ = z;
						maxZInx = i;
					}
				}
			if (maxZ != MIN_Z)
				drawPoints.emplace_back(point, colors[maxZInx]);
		}
		else
		{
			auto nextRects = SplitRect(rect);
			for (auto&& nextRect : nextRects)
				rectStack.push(nextRect);
		}

	}
	else
		return;
}

bool WarnockAlgorithm::IsTriangleOutsideRect(const sf::Rect<int>& rect, const Triangle& triangle)
{
	auto triangleRect = static_cast<sf::Rect<int>>(triangle.GetRect());
	return !IsRectsIntersect(triangleRect, rect);
}

bool WarnockAlgorithm::IsPointInTriangle2d(sf::Vector2f point, const Triangle& triangle)
{
	sf::Vector2f	p[]{
		{triangle.p1.x, triangle.p1.y},
		{triangle.p2.x, triangle.p2.y},
		{triangle.p3.x, triangle.p3.y}
	};
	float sign = VectorHelper::CrossProd(point - p[0], p[1] - p[0]);
	for (int i = 1; i < 3; i++)
		if (VectorHelper::CrossProd(point - p[i], p[(i + 1) % 3] - p[i]) * sign < 0)
			return false;
	return true;
}

bool WarnockAlgorithm::IsRectsIntersect(const sf::Rect<int>& r1, const sf::Rect<int>& r2)
{
	int r1r = r1.left + r1.width, r1b = r1.top + r1.height, r2r = r2.left + r2.width, r2b = r2.top + r2.height;
	return !(r1.left > r2r || r2.left > r1r || r1.top > r2b || r2.top > r1b);
}

float WarnockAlgorithm::GetZ(sf::Vector2f p, const Triangle& triangle)
{
	auto plane = triangle.CalcPlane();
	if (abs(plane.c) < 1e-5)
		return std::max(triangle.p1.z, std::max(triangle.p2.z, triangle.p3.z));
	return plane.GetZ(p.x, p.y);
}

std::vector<sf::Rect<int>> WarnockAlgorithm::SplitRect(const sf::Rect<int>& rect)
{
	std::vector<sf::Rect<int>> nextRects;
	int l = rect.left, r = rect.left + rect.width, t = rect.top, b = rect.top + rect.height;
	sf::Vector2i c{ (l + r) / 2, (t + b) / 2 };
	if (rect.width > 1 && rect.height > 1)
		return {
			{l,t,c.x - l, c.y - t},
			{c.x, t, r - c.x, c.y - t},
			{l,c.y,c.x - l, b - c.y},
			{c.x, c.y, r - c.x, b - c.y} };
	if (rect.width > 1)
		return {
			{l, t, c.x - l, b - t},
			{c.x, t, r - c.x, b - t} };
	if (rect.height > 1)
		return {
			{l, t, r - l, c.y - t},
			{l, c.y, r - l, b - c.y} };
	return {};
}

void WarnockAlgorithm::DrawStack(sf::RenderWindow& window)
{
	auto stackCopy = rectStack;
	while(!stackCopy.empty())
	{
		DrawRect(window, stackCopy.top());
		stackCopy.pop();
	}
}

void WarnockAlgorithm::DrawRect(sf::RenderWindow& window, const sf::Rect<int>& r)
{
	sf::Vector2f tl{(float)r.left, (float)r.top};
	sf::Vector2f br{(float)(r.left+r.width), (float)(r.top+r.height)};
	
	sf::VertexArray shape(sf::LineStrip, 5);
	shape[0] = sf::Vertex(tl, sf::Color::White);
	shape[1] = sf::Vertex({tl.x, br.y}, sf::Color::White);
	shape[2] = sf::Vertex(br, sf::Color::White);
	shape[3] = sf::Vertex({br.x, tl.y}, sf::Color::White);
	shape[4] = sf::Vertex(tl, sf::Color::White);
	window.draw(shape);
}

