#pragma once
#include "Actor.h"

class Sprite;

class SpriteEffect : public Actor
{
	GENERATE_BODY(SpriteEffect, Actor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void UpdateAnimation();
private:
	std::shared_ptr<Sprite> _Sprite;


};

