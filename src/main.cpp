#include <fstream>
#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "Scene.h"
#include "Vector3Animation.h"
#include "Figure/TriangleMeshFigure.h"
#include "Figure/WireFigure.h"


WireFigure ReadWireFigure(std::ifstream& fin, sf::Vector3f& animatedScale)
{
	std::vector<std::vector<float>> dots;
	int n, m;
	fin >> n >> m;
	while (n--)
	{
		float x, y, z;
		fin >> x >> y >> z;
		dots.push_back({ x,y,z,1 });
	}
	WireFigure fig(dots);
	while (m--)
	{
		size_t first, second;
		fin >> first >> second;
		fig.SetLine(first - 1, second - 1);
	}
	fin >> animatedScale.x >> animatedScale.y >> animatedScale.z;
	return fig;
}

TriangleMeshFigure ReadTriangleMeshFigure(std::ifstream& fin)
{
	std::vector<std::vector<float>> dots;
	int n, m;
	fin >> n >> m;
	while (n--)
	{
		float x, y, z;
		fin >> x >> y >> z;
		dots.push_back({ x,y,z,1 });
	}
	TriangleMeshFigure fig(dots);
	while (m--)
	{
		size_t first, second, third;
		fin >> first >> second >> third;
		fig.SetTriangle(first - 1, second - 1, third - 1);
	}
	int r, g, b;
	fin >> r >> g >> b;
	fig.SetColor(r, g, b);
	return fig;
}

int main()
{
	std::ifstream fin("figure.txt");
	sf::RenderWindow window(sf::VideoMode(500, 500), "Hide invisible lines");
	sf::Clock clock;
	Vector3Animation anim;
	sf::Vector3f animScaleCoefs{ 1,1.2,1.2 },
		XYZCenter = { static_cast<float>(window.getSize().x) / 3, static_cast<float>(window.getSize().y) / 2, 0 };

	Scene scene;
	scene.SetScale({ 1,-1, 1 });
	scene.Translate(XYZCenter);

	scene.AddFigure(ReadTriangleMeshFigure(fin));
	scene.AddFigure(ReadTriangleMeshFigure(fin));
	
	bool stepDraw = false;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		auto dt = clock.restart().asSeconds();
		auto& fig = scene.GetSelectedFigure();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			fig.Translate(sf::Vector3f{ 0,100, 0 } *dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			fig.Translate(sf::Vector3f{ 0,-100, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			fig.Translate(sf::Vector3f{ -100,0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			fig.Translate(sf::Vector3f{ 100,0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			fig.Translate(sf::Vector3f{ 0,0, 100 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			fig.Translate(sf::Vector3f{ 0,0, -100 }*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
			fig.Scale(sf::Vector3f{ 0, 2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			fig.Scale(sf::Vector3f{ 0, -2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			fig.Scale(sf::Vector3f{ -2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
			fig.Scale(sf::Vector3f{ 2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
			fig.Scale(sf::Vector3f{ 0, 0, 2.f }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
			fig.Scale(sf::Vector3f{ 0, 0, -2.f }*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			fig.Rotate(sf::Vector3f{ -2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			fig.Rotate(sf::Vector3f{ 2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			fig.Rotate(sf::Vector3f{ 0, 2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			fig.Rotate(sf::Vector3f{ 0, -2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			fig.Rotate(sf::Vector3f{ 0, 0, 2.f }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			fig.Rotate(sf::Vector3f{ 0, 0, -2.f }*dt);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			scene.SelectFigure(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			scene.SelectFigure(1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			scene.Reset();
			scene.SetScale({ 1,-1, 1 });
			scene.Translate(XYZCenter);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
			stepDraw = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			if (!anim.IsStarted()) {
				const auto& currScale = fig.GetScale();
				auto nextScale = sf::Vector3f(currScale.x * animScaleCoefs.x, currScale.y * animScaleCoefs.y, currScale.z * animScaleCoefs.z);
				anim.Start(nextScale - currScale);
			}
		}

		if (anim.IsStarted())
			fig.Scale(anim.GetProgress(dt));


		window.clear(sf::Color::Black);
		Transform transform;
		transform.ProjectOnXY();
		if (stepDraw)
		{
			window.display();
			scene.StepDraw(window, transform);
			stepDraw = false;
		}
		else
			scene.Draw(window, transform);

		window.display();
	}
}