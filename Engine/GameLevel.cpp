#include "pch.h"
#include "GameLevel.h"
#include "SpriteActor.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::Init()
{
	// Temp
	{
		std::shared_ptr<SpriteActor> background = std::make_shared<SpriteActor>();
		background->SetPos({ 0, 0 });

		AddActor(background);
	}
	Super::Init();
}

void GameLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void GameLevel::Render(HDC hdc)
{
	Super::Render(hdc);

}
