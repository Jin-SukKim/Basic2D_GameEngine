#include "pch.h"
#include "World.h"
#include "Engine.h"

World::World()
{
	_timeManager = std::make_unique<TimeManager>();
}

World::~World()
{
}

void World::Init()
{
}

void World::Tick()
{
	float deltaTime = GetWorldTimer().GetDeltaTime();
}

void World::Render(HDC hdc)
{
	
}
