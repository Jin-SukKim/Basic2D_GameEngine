#include "pch.h"
#include "Engine.h"
#include "World.h"

Engine::Engine()
{
	_world = std::make_unique<World>();
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	return true;

	_world->Init();
}

void Engine::Tick()
{
	_world->Tick();
}

void Engine::Render()
{
	uint32 prevTick = 0;
	{
		std::wstring str = std::format(L"Mouse({0}, {1})", _mousePosX, _mousePosY);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size())); uint64 prevTick = 0;
	}

	{
		uint32 now = static_cast<uint32>(::GetTickCount64());

		int width = _screenWidth;

		uint32 fps = now - prevTick;
		std::wstring str = std::format(L"FPS({0}))", fps);
		::TextOut(_hdcBack, width - 200, 10, str.c_str(), static_cast<int32>(str.size()));
		prevTick = now;
	}
	_world->Render(_hdcBack);

}
