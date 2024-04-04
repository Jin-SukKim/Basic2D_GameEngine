#include "pch.h"
#include "GameLevel.h"
#include "SpriteActor.h"
#include "TilemapActor.h"
#include "Player.h"

GameLevel::GameLevel()
{
	// Temp background
	{
		std::shared_ptr<SpriteActor> background = std::make_shared<SpriteActor>();
		background->SetPos({ 0, 0 });

		AddActor(background);
	}

	// flipbook
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->SetPos({ 400, 300 });

		AddActor(player);
	}

	// Tilemap
	{
		std::shared_ptr<TilemapActor> tilemap = std::make_shared<TilemapActor>();
		tilemap->SetShowDebug(false);

		AddActor(tilemap);
	}
}

GameLevel::~GameLevel()
{
}

void GameLevel::Init()
{
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
