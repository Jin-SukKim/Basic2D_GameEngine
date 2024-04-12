#include "pch.h"
#include "Engine.h"
#include "World\World.h"
#include "Manager\InputManager.h"
#include "Manager\AssetManager.h"

Engine::Engine() : EngineWindow()
{
	_world = std::make_unique<World>();
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	GET_SINGLE(InputManager)->Init(_hwnd);
	GET_SINGLE(AssetManager)->Init(_hwnd);

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
