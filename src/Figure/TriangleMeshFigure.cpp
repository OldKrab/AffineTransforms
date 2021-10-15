#include "TriangleMeshFigure.h"

#include <SFML/Graphics/ConvexShape.hpp>

#include "WarnockAlgorithm.h"
#include "Math/Triangle.h"
#include "Math/VectorHelper.h"

TriangleMeshFigure::TriangleMeshFigure(Matrix<float> dots) :TriangleMeshFigure(std::move(dots), std::vector<TriangleInxs>(), sf::Color::White) {}

TriangleMeshFigure::TriangleMeshFigure(Matrix<float> dots, std::vector<TriangleInxs> trianglesInxs, sf::Color color)
	: dots_(std::move(dots)), trianglesInxs_(std::move(trianglesInxs)), color_(color) {}

const Matrix<float>& TriangleMeshFigure::GetDots() const
{
	return dots_;
}

Matrix<float> TriangleMeshFigure::GetTransformedDots() const
{
	return dots_ * GetTransform().GetMatrix();
}

void TriangleMeshFigure::GetTrianglesAndColors(std::vector<Triangle>& triangles, std::vector<sf::Color>& colors, const Transform& trans) const
{
	auto resTransform = GetTransform().GetCombination(trans);
	auto newDots = dots_ * resTransform.GetMatrix();
	triangles.reserve(triangles.capacity() + trianglesInxs_.size());
	colors.reserve(colors.capacity() + trianglesInxs_.size());
	for (const auto& triangleInxs : trianglesInxs_)
	{
		const auto& dots = std::vector<sf::Vector3f>
		{
			VectorHelper::GetVector3fFromFourCrds(newDots[triangleInxs.firstInx]),
			VectorHelper::GetVector3fFromFourCrds(newDots[triangleInxs.secondInx]),
			VectorHelper::GetVector3fFromFourCrds(newDots[triangleInxs.thirdInx])
		};
		Triangle triangle = { dots[0], dots[1], dots[2] };

		auto norm = VectorHelper::Normalize(triangle.CalcPlane().GetNorm());
		float colorCoef = abs(VectorHelper::DotProd(norm, { 0,0,1 }));
		sf::Color col;
		col.r = static_cast<uint8_t>(static_cast<float>(color_.r) * colorCoef);
		col.g = static_cast<uint8_t>(static_cast<float>(color_.g) * colorCoef);
		col.b = static_cast<uint8_t>(static_cast<float>(color_.b) * colorCoef);

		triangles.push_back(triangle);
		colors.emplace_back(col);
	}
}

const std::vector<TriangleMeshFigure::TriangleInxs>& TriangleMeshFigure::GetTrianglesInxs() const
{
	return trianglesInxs_;
}

void TriangleMeshFigure::SetTriangle(size_t firstInx, size_t secondInx, size_t thirdInx)
{
	trianglesInxs_.push_back({ firstInx, secondInx, thirdInx });
}

void TriangleMeshFigure::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
	color_ = { r,g,b };
}

TriangleMeshFigure TriangleMeshFigure::Combine(TriangleMeshFigure other) const
{
	other.dots_.InsertBack(dots_);
	other.trianglesInxs_.insert(other.trianglesInxs_.begin(), trianglesInxs_.begin(), trianglesInxs_.end());
	return other;
}

void TriangleMeshFigure::Draw(sf::RenderTarget& target, const Transform& trans) const
{
	std::vector<Triangle> triangles;
	std::vector<sf::Color> colors;
	GetTrianglesAndColors(triangles, colors, trans);
	WarnockAlgorithm wa(triangles, colors);
	wa.Run(target);
}
