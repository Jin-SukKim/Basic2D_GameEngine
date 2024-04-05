#pragma once
#include "FlipbookActor.h"

class SquareComponent;

class Enemy : public FlipbookActor
{
	GENERATE_BODY(Enemy, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	std::shared_ptr<SquareComponent> _square;
};

