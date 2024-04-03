#pragma once
#include "Level.h"

class GameLevel : public Level
{
	GENERATE_BODY(GameLevel, Level)
public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

};

