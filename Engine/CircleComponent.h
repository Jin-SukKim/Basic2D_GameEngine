#pragma once
#include "Collider.h"
class CircleComponent : public Collider
{
	GENERATE_BODY(CircleComponent, Collider)
public:

public:
	void SetRadius(const float& radius) { _radius = radius; }
	float GetRadius() const { return _radius; }
private:
	float _radius = 0.f;
};

