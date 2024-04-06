#include "pch.h"
#include "World.h"
#include "Engine.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "CollisionManager.h"

World::World()
{
	_timeManager = std::make_unique<TimeManager>();
	_levelManager = std::make_unique<LevelManager>();
}

World::~World()
{
}

void World::Init()
{
	_timeManager->Init();
	_levelManager->Init();
	_levelManager->ChangeLevel(LevelType::LEVEL_GAME);

	GET_SINGLE(CollisionManager)->Init();
}


void World::Tick()
{
	_timeManager->Tick();
	float deltaTime = _timeManager->GetDeltaTime();

	GET_SINGLE(CollisionManager)->Tick();

	_levelManager->Tick(deltaTime);

}

void World::Render(HDC hdc)
{
	_levelManager->Render(hdc);

	// Option
	{
		uint32 now = static_cast<uint32>(::GetTickCount64());
		{
			auto [mousePosX, mousePosY] = GET_SINGLE(InputManager)->GetMousePos();
			std::wstring str = std::format(L"Mouse({0}, {1})", mousePosX, mousePosY);
			::TextOut(hdc, 20, 10, str.c_str(), static_cast<int32>(str.size())); uint64 prevTick = 0;
		}

		{
			int width = Engine::GetScreenWidth();

			std::wstring str = std::format(L"FPS({0}))", _timeManager->GetFPS());
			::TextOut(hdc, width - 90, 10, str.c_str(), static_cast<int32>(str.size()));

		}
	}
}
