#include "pch.h"
#include "Engine.h"
#include "World.h"
#include "InputManager.h"

Engine::Engine() : EngineWindow()
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	GET_SINGLE(InputManager)->Init(_hwnd);

	_world = std::make_unique<World>();
	_world->Init();

	return true;
}

void Engine::Tick()
{
	GET_SINGLE(InputManager)->Tick();
	_world->Tick();
}

void Engine::Render()
{
	_world->Render(_hdcBack);
}
