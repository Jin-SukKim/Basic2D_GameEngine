#pragma once
#include "Level.h"

class GameLevel : public Level
{
	using Super = Level;
public:
	GameLevel();
	virtual ~GameLevel() override;

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

};

