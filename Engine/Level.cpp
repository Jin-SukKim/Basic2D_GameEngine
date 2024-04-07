#include "pch.h"
#include "Level.h"
#include "Actor.h"
#include "CollisionManager.h"
#include "TilemapActor.h"
#include "Tilemap.h"

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
	v.push_back(std::move(actor));
}

void Level::RemoveActor(std::weak_ptr<Actor> actor)
{
	std::shared_ptr<Actor> cachedActor = actor.lock();
	if (cachedActor == nullptr)
		return;

	std::vector<std::shared_ptr<Actor>>& v = _actors[cachedActor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), cachedActor), v.end());
}

int32 Level::GetActorCount()
{
	size_t count = 0;
	for (auto actors : _actors)
			count += actors.size();
	
	return static_cast<int32>(count);
}

std::shared_ptr<Tilemap> Level::GetCurTilemap()
{
	if (_curTilemapActor == nullptr)
		return nullptr;
	return GetCurrentTilemapActor()->GetTilemap();
}
