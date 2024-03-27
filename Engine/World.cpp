#include "pch.h"
#include "World.h"
#include "Engine.h"
#include "InputManager.h"

World::World()
{
	_timeManager = std::make_unique<TimeManager>();
}

World::~World()
{
}

void World::Init()
{
	_timeManager->Init();
}

void World::Tick()
{
	_timeManager->Tick();
}

void World::Render(HDC hdc)
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
		::TextOut(hdc, width - 200, 10, str.c_str(), static_cast<int32>(str.size()));
		
	}
}
