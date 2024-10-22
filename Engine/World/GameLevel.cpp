#include "pch.h"
#include "GameLevel.h"
#include "Actor\SpriteActor.h"
#include "Actor\TilemapActor.h"
#include "Actor\Player.h"
#include "Actor\Enemy.h"

GameLevel::GameLevel()
{
	// Temp background
	{
		std::shared_ptr<SpriteActor> background = std::make_shared<SpriteActor>();
		background->SetPos({ 0, 0 });

		AddActor(background);
	}

	// Tilemap
	{
		std::shared_ptr<TilemapActor> tilemap = std::make_shared<TilemapActor>();
		SetCurrentTilemapActor(tilemap);
		tilemap->SetShowDebug(false);

		AddActor(tilemap);
	}
	// Enemy
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->SetPos({ 700, 300 });

		AddActor(enemy);
	}
	// Actor
	{
		std::shared_ptr<Player> player = std::make_shared<Player>();
		player->SetPos({ 400, 300 });
		player->SetSize({ 48.f, 48.f});

		AddActor(player);
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
