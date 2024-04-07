#include "pch.h"
#include "GameLevel.h"
#include "SpriteActor.h"
#include "TilemapActor.h"
#include "Player.h"
#include "Enemy.h"

GameLevel::GameLevel()
{
	// Temp background
	{
		std::shared_ptr<SpriteActor> background = std::make_shared<SpriteActor>();
		background->SetPos({ 0, 0 });

		AddActor(background);
	}

	// Actor
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->SetPos({ 400, 300 });

		AddActor(player);
	}
	// Enemy
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->SetPos({ 700, 300 });

		AddActor(enemy);
	}

	// Tilemap
	{
		std::shared_ptr<TilemapActor> tilemap = std::make_shared<TilemapActor>();
		SetCurrentTilemapActor(tilemap);
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
