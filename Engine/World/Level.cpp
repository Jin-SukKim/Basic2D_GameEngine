#include "pch.h"
#include "Level.h"
#include "Actor\Actor.h"
#include "Manager\CollisionManager.h"
#include "Actor\TilemapActor.h"
#include "Resources\Tilemap.h"
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

	for (auto& actors : _actors) {
		for (std::shared_ptr<Actor> actor : actors) {
			if (actor)
				actor->Tick(DeltaTime);
		}
	}
}

void Level::Render(HDC hdc)
{
	for (auto& actors : _actors) {
		for (std::shared_ptr<Actor> actor : actors) {
			if (actor)
				actor->Render(hdc);
		}
	}
}

void Level::AddActor(std::shared_ptr<Actor> actor)
{
	if (actor == nullptr)
		return;

	std::vector<std::shared_ptr<Actor>>& v = _actors[actor->GetLayer()];
	v.push_back(actor);
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

std::shared_ptr<Actor> Level::FindClosestTarget(Vector2D pos)
{
	float best = FLT_MAX;
	std::shared_ptr<Actor> target = nullptr;

	for (std::shared_ptr<Actor> actor : _actors[LayerType::LT_OBJECT]) {
		if (actor->GetTag() == L"Player") {
			Vector2D dir = pos - actor->GetPos();
			float dist = dir.LengthSquared();
			if (dist < best) {
				best = dist;
				target = actor;
			}
		}
	}

	return target;
}


std::shared_ptr<Tilemap> Level::GetCurTilemap()
{
	if (GetCurrentTilemapActor() == nullptr)
		return nullptr;
	return GetCurrentTilemapActor()->GetTilemap();
}

