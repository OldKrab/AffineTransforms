#include "TriangleMeshFigureList.h"

#include "WarnockAlgorithm.h"

void TriangleMeshFigureList::AddFigure(const TriangleMeshFigure& figure)
{
	figures.push_back(figure);
}

TriangleMeshFigure& TriangleMeshFigureList::GetFigure(size_t inx) 
{
	return figures[inx];
}

size_t TriangleMeshFigureList::GetSize() const
{
	return figures.size();
}

void TriangleMeshFigureList::Draw(sf::RenderTarget& target, const Transform& trans) const
{
	std::vector<Triangle> triangles;
	std::vector<sf::Color> colors;
	for(auto&& fig: figures)
		fig.GetTrianglesAndColors(triangles, colors, trans);
	
	WarnockAlgorithm wa(triangles, colors);
	wa.Run(target);
}

void TriangleMeshFigureList::StepDraw(sf::RenderWindow& window, const Transform& trans) const
{
	
	std::vector<Triangle> triangles;
	std::vector<sf::Color> colors;
	for(auto&& fig: figures)
		fig.GetTrianglesAndColors(triangles, colors, trans);
	
	WarnockAlgorithm wa(triangles, colors);
	wa.StepRun(window);
}

void TriangleMeshFigureList::Reset()
{
	for(auto&& fig:figures)
		fig.ResetTransform();
}


