#pragma once
#include "FlipbookActor.h"

class Sprite;

class SpriteEffect : public FlipbookActor
{
	GENERATE_BODY(SpriteEffect, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void UpdateAnimation();
};

