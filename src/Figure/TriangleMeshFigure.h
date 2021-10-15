#pragma once
#include "BaseFigure.h"
#include "Math/Triangle.h"


class TriangleMeshFigure :public BaseFigure
{
public:
	struct TriangleInxs
	{
		size_t firstInx, secondInx, thirdInx;
	};
	TriangleMeshFigure(Matrix<float> dots);
	TriangleMeshFigure(Matrix<float> dots, std::vector<TriangleInxs> trianglesInxs, sf::Color color);
	void SetTriangle(size_t firstInx, size_t secondInx, size_t thirdInx);
	void SetColor(uint8_t r, uint8_t g, uint8_t b);
	
	const Matrix<float>& GetDots() const;
	Matrix<float> GetTransformedDots() const;
	void GetTrianglesAndColors(std::vector<Triangle>& triangles, std::vector<sf::Color> & colors, const Transform& trans) const;
	const std::vector<TriangleInxs>& GetTrianglesInxs() const;
	
	TriangleMeshFigure Combine(TriangleMeshFigure other) const;
	void Draw(sf::RenderTarget& target, const Transform& trans) const override;
private:
	Matrix<float> dots_;
	std::vector<TriangleInxs> trianglesInxs_;
	sf::Color color_;
};
