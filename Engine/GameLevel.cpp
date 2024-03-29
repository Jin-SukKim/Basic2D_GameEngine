#include "pch.h"
#include "GameLevel.h"
#include "TextureActor.h"

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
		std::shared_ptr<TextureActor> background = std::make_shared<TextureActor>();
		background->SetPos({ 400, 300 });

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
