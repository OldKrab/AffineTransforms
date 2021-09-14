#include "Vector3Animation.h"
#include <cassert>

Vector3Animation::Vector3Animation()
{
	animationCurve_ = [](float t) { return (t - 1) * (t - 1) * (t - 1) + 1; };
}

void Vector3Animation::Start(sf::Vector3f vec)
{
	currVector_ = {0, 0, 0};
	elapsedTime_ = 0;
	leftVector_ = vec;
	isStarted_ = true;
}

void Vector3Animation::SetAnimationCurve(std::function<float(float)> animCurve)
{
	animationCurve_ = std::move(animCurve);
}

sf::Vector3f Vector3Animation::GetProgress(float dt)
{
	assert(isStarted_);

	elapsedTime_ += dt;
	if (elapsedTime_ > duration_)
	{
		elapsedTime_ = duration_;
		isStarted_ = false;
	}
	auto deltaVec = animationCurve_(elapsedTime_ / duration_) * leftVector_ - currVector_;
	currVector_ += deltaVec;
	return deltaVec;
}

bool Vector3Animation::IsStarted() const
{
	return isStarted_;
}
