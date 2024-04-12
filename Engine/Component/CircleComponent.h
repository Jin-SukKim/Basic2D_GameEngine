#pragma once
#include "Collider.h"
class CircleComponent : public Collider
{
	GENERATE_BODY(CircleComponent, Collider)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(std::weak_ptr<Collider> other);
public:
	void SetRadius(const float& radius) { _radius = radius; }
	float GetRadius() const { return _radius; }
private:
	float _radius = 0.f;
};

