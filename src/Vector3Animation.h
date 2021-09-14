#pragma once
#include <functional>
#include <SFML/System/Vector3.hpp>

class Vector3Animation
{
public:
	Vector3Animation();

	// start changing vector from {0,0,0} to vec
	void Start(sf::Vector3f vec);

	// animCurve(0) = 0, animCurve(1) = 1
	void SetAnimationCurve(std::function<float(float)> animCurve);

	sf::Vector3f GetProgress(float dt);

	bool IsStarted() const;

private:
	std::function<float(float)> animationCurve_;
	float elapsedTime_ = 0, duration_ = 1.f;
	bool isStarted_ = false;
	sf::Vector3f currVector_, leftVector_;
};
