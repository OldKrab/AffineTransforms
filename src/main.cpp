#include <fstream>
#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "Vector3Animation.h"
#include "Figure.h"

Figure InitAxes()
{
	auto dots = Matrix<float>({
		{0, 0, 0, 1},
		{2000, 0, 0, 1},
		{0, 2000, 0, 1},
		{0, 0, 3000, 1} });

	Figure axes(dots);
	axes.SetLine(0, 1);
	axes.SetLine(0, 2);
	axes.SetLine(0, 3);

	return axes;
}

Figure ReadCustomFigure(sf::Vector3f& animatedScale)
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
	Figure fig(dots);
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
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
	sf::Clock clock;
	Vector3Animation anim;
	sf::Vector3f animScaleCoefs, globalCenter = { 300, 300, 0 };

	auto axes = InitAxes();
	auto fig = ReadCustomFigure(animScaleCoefs);
	axes.SetGlobalCenter(globalCenter);
	fig.SetGlobalCenter(globalCenter);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		auto dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			fig.AddTranslation(sf::Vector3f{ 0,100, 0 } *dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			fig.AddTranslation(sf::Vector3f{ 0,-100, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			fig.AddTranslation(sf::Vector3f{ -100,0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			fig.AddTranslation(sf::Vector3f{ 100,0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			fig.AddTranslation(sf::Vector3f{ 0,0, 100 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			fig.AddTranslation(sf::Vector3f{ 0,0, -100 }*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
			fig.AddScale(sf::Vector3f{ 0, 2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			fig.AddScale(sf::Vector3f{ 0, -2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			fig.AddScale(sf::Vector3f{ -2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
			fig.AddScale(sf::Vector3f{ 2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
			fig.AddScale(sf::Vector3f{ 0, 0, 2.f }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
			fig.AddScale(sf::Vector3f{ 0, 0, -2.f }*dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			fig.AddRotate(sf::Vector3f{ 0, 0, 2.f }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			fig.AddRotate(sf::Vector3f{ 0, 0, -2.f }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			fig.AddRotate(sf::Vector3f{ 0, 2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			fig.AddRotate(sf::Vector3f{ 0, -2.f, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			fig.AddRotate(sf::Vector3f{ 2.f, 0, 0 }*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			fig.AddRotate(sf::Vector3f{ -2.f, 0, 0 }*dt);

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			axes.AddRotate(sf::Vector3f{ 0, -2.f, 0 }*dt);
			fig.AddRotate(sf::Vector3f{ 0, -2.f, 0 }*dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			axes.AddRotate(sf::Vector3f{ 0, 2.f, 0 }*dt);
			fig.AddRotate(sf::Vector3f{ 0, 2.f, 0 }*dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			axes.AddRotate(sf::Vector3f{ 0, 0, 2.f }*dt);
			fig.AddRotate(sf::Vector3f{ 0, 0, 2.f }*dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			axes.AddRotate(sf::Vector3f{ 0, 0, -2.f }*dt);
			fig.AddRotate(sf::Vector3f{ 0, 0, -2.f }*dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
			axes.AddRotate(sf::Vector3f{ 2.f, 0, 0 }*dt);
			fig.AddRotate(sf::Vector3f{ 2.f, 0, 0 }*dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
			axes.AddRotate(sf::Vector3f{ -2.f, 0, 0 }*dt);
			fig.AddRotate(sf::Vector3f{ -2.f, 0, 0 }*dt);
		}
		if (anim.IsStarted())
			fig.AddScale(anim.GetProgress(dt));
		
		window.clear(sf::Color::Black);
		window.draw(axes);
		window.draw(fig);
		window.display();
	}
}