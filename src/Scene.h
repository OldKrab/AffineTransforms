#pragma once
#include "Figure/TriangleMeshFigure.h"
#include "Figure/TriangleMeshFigureList.h"
#include "Figure/WireFigure.h"

class Scene :public IDrawable, public ITransformable
{
public:
	Scene();
	void AddFigure(const TriangleMeshFigure& fig);
	void SelectFigure(size_t inx);
	TriangleMeshFigure& GetSelectedFigure();
	void Draw(sf::RenderTarget& target, const Transform& trans) const override;
	void StepDraw(sf::RenderWindow& window, const Transform& trans) const;
	void Reset();
	void InitAxes();
private:
	TriangleMeshFigureList triangleFigures;
	size_t selectedFigure;
	WireFigure axes;
};

