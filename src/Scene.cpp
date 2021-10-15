#include "Scene.h"

Scene::Scene() :selectedFigure(0)
{
	InitAxes();
}

void Scene::AddFigure(const TriangleMeshFigure& fig)
{
	triangleFigures.AddFigure(fig);
}

void Scene::SelectFigure(size_t inx)
{
	selectedFigure = inx;
}

 TriangleMeshFigure& Scene::GetSelectedFigure()
{
	return triangleFigures.GetFigure(selectedFigure);
}

void Scene::Draw(sf::RenderTarget& target, const Transform& trans) const
{
	auto&& newTrans = trans.GetCombination(GetTransform());
	triangleFigures.Draw(target, newTrans);
	axes.Draw(target, newTrans);
}

void Scene::StepDraw(sf::RenderWindow& window, const Transform& trans) const
{
	auto&& newTrans = trans.GetCombination(GetTransform());
	triangleFigures.StepDraw(window, newTrans);
}

void Scene::Reset()
{
	ResetTransform();
	triangleFigures.Reset();
}

void Scene::InitAxes()
{
	auto dots = Matrix<float>({
		{0, 0, 0, 1},
		{2000, 0, 0, 1},
		{0, 2000, 0, 1},
		{0, 0, 3000, 1}
		});

	axes = WireFigure(dots);
	axes.SetLine(0, 1);
	axes.SetLine(0, 2);
	axes.SetLine(0, 3);
}
