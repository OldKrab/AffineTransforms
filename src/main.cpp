#include <fstream>
#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "Vector3Animation.h"
#include "Figure/WireFigure.h"

WireFigure InitAxes()
{
	auto dots = Matrix<float>({
		{0, 0, 0, 1},
		{2000, 0, 0, 1},
		{0, 2000, 0, 1},
		{0, 0, 3000, 1} });

	WireFigure axes(dots);
	axes.SetLine(0, 1);
	axes.SetLine(0, 2);
	axes.SetLine(0, 3);

	return axes;
}

WireFigure ReadCustomFigure(sf::Vector3f& animatedScale)
{
	std::ifstream fin("figure.txt");
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

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Affine Transforms");
	sf::Clock clock;
	Vector3Animation anim;
	sf::Vector3f animScaleCoefs, globalCenter = { 300, 300, 0 };

	auto axes = InitAxes();
	auto fig = ReadCustomFigure(animScaleCoefs);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		auto dt = clock.restart().asSeconds();

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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			fig.ResetTransform();
			axes.ResetTransform();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			if (!anim.IsStarted()) {
				auto currScale = fig.GetScale();
				auto nextScale = sf::Vector3f(currScale.x * animScaleCoefs.x, currScale.y * animScaleCoefs.y, currScale.z * animScaleCoefs.z);
				anim.Start(nextScale - currScale);
			}
		}
		

		if (anim.IsStarted())
			fig.Scale(anim.GetProgress(dt));
		window.clear(sf::Color::Black);
		Transform transform;
		transform.Translate(globalCenter);
		transform.ProjectOnXY();
		axes.Draw(window, transform);
		fig.Draw(window, transform);
		window.display();
	}
}