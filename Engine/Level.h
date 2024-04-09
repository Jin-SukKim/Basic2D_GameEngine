#pragma once

#include "TilemapActor.h"
class Actor;
class CollisionManager;
class TilemapActor;
class Level
{
public:
	Level();
	virtual ~Level();

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc);

	virtual void AddActor(std::shared_ptr<Actor> actor);
	virtual void RemoveActor(std::weak_ptr<Actor> actor);

	int32 GetActorCount();

	std::shared_ptr<Actor> FindClosestTarget(Vector2D pos);
public:
	static void SetCurrentTilemapActor(std::shared_ptr<TilemapActor> tilemapActor) { _curTilemapActor = tilemapActor;	}
	static std::shared_ptr<TilemapActor> GetCurrentTilemapActor() { return _curTilemapActor; }
	static std::shared_ptr<Tilemap> GetCurTilemap();

private:
	// TODO: Actor ������ unordered_map���� �ϴ°� �� ��������?, level���ٴ� world���� �����ϴ°� �����Ͱ���.
	// TODO: Level�� ������ ���̹Ƿ� level�� ���� Actor�� ���� �����ϴ°� ������ ����.
	// (��, World�� ���� actor�� level�� ���� actor�� �����°�?)
	// Layer���� ������ ������� Rendering (ex: background -> object, �̷��� object�� background���� ���δ�)
	std::vector<std::shared_ptr<Actor>> _actors[LT_MAXCOUNT]; // ���� 2D �����̶� �̷��� �� ��, 3D�� Depth������ Ȯ��

	// TODO: Level���� static���ٴ� UEó�� GetWorld�� �޾ƿµ� Level�� ������ ����ϴ°� �� ������ʹ�.
	static inline std::shared_ptr<TilemapActor> _curTilemapActor = nullptr;;
};

