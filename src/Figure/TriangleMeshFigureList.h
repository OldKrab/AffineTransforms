#pragma once
#include <list>
#include <SFML/Graphics/RenderWindow.hpp>

#include "TriangleMeshFigure.h"

class TriangleMeshFigureList:public BaseFigure
{
public:
	void AddFigure(const TriangleMeshFigure& figure);
	TriangleMeshFigure& GetFigure(size_t inx);
	size_t GetSize() const;
	
	void Draw(sf::RenderTarget& target, const Transform& trans) const override;
	void StepDraw(sf::RenderWindow& window, const Transform& trans) const;
	void Reset();
private:
	
	std::vector<TriangleMeshFigure> figures;
};
