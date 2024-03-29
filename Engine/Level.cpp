#include "pch.h"
#include "Level.h"
#include "Actor.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Init()
{
	for (auto& actors : _actors)
		for (std::shared_ptr<Actor>& actor : actors)
			actor->Init();
}

void Level::Tick(float DeltaTime)
{
	for (auto& actors : _actors)
		for (std::shared_ptr<Actor>& actor : actors)
			actor->Tick(DeltaTime);
}

void Level::Render(HDC hdc)
{
	for (auto& actors : _actors)
		for (std::shared_ptr<Actor>& actor : actors)
			actor->Render(hdc);

}

void Level::AddActor(std::shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	std::vector<std::shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
	v.push_back(actor);
}

void Level::RemoveActor(std::shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	std::vector<std::shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

int32 Level::GetActorCount()
{
	int32 count = 0;
	for (auto actors : _actors)
			count += actors.size();
	
	return count;
}
