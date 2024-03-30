#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "GameLevel.h"
#include "EditLevel.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init()
{
	_level = std::make_unique<Level>();
}

void LevelManager::Tick(float DeltaTime)
{
	if (_level.get())
		_level->Tick(DeltaTime);
}

void LevelManager::Render(HDC hdc)
{
	if (_level.get())
		_level->Render(hdc);
}

void LevelManager::ChangeLevel(LevelType levelType)
{
	if (_levelType == levelType)
		return;

	std::unique_ptr<Level> newLevel;

	switch (levelType)
	{
	case LevelType::LEVEL_DEFAULT:
		break;
	case LevelType::LEVEL_GAME:
		newLevel = std::make_unique<GameLevel>();
		break;
	case LevelType::LEVEL_EDIT:
		newLevel = std::make_unique<EditLevel>();
		break;
	default:
		break;
	}

	_level = nullptr;
	_level = std::move(newLevel);

	_level->Init();
}

void LevelManager::SetLevel(std::unique_ptr<Level> level)
{
	if (_level == level)
		return;

	_level = nullptr;
	_level = std::move(level);

	_level->Init();
}
