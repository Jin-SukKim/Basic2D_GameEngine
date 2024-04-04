#pragma once
#include "Collider.h"

class SquareComponent : public Collider
{
	GENERATE_BODY(SquareComponent, Collider)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(std::weak_ptr<Collider> other);
};

