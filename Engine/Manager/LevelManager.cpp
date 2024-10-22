#include "pch.h"
#include "LevelManager.h"
#include "World\Level.h"
#include "World\GameLevel.h"
#include "World\EditLevel.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init()
{
	_level = std::make_shared<Level>();
}

void LevelManager::Tick(float DeltaTime)
{
	if (_level)
		_level->Tick(DeltaTime);
}

void LevelManager::Render(HDC hdc)
{
	if (_level)
		_level->Render(hdc);
}

void LevelManager::ChangeLevel(LevelType levelType)
{
	if (_levelType == levelType)
		return;

	std::shared_ptr<Level> newLevel;

	switch (levelType)
	{
	case LevelType::LEVEL_DEFAULT:
		break;
	case LevelType::LEVEL_GAME:
		newLevel = std::make_shared<GameLevel>();
		break;
	case LevelType::LEVEL_EDIT:
		newLevel = std::make_shared<EditLevel>();
		break;
	default:
		break;
	}

	_level = nullptr;
	_level = std::move(newLevel);

	_level->Init();
}

void LevelManager::SetLevel(std::shared_ptr<Level> level)
{
	if (_level == level)
		return;

	_level = nullptr;
	_level = std::move(level);

	_level->Init();
}
