#pragma once

class Actor;

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

public:
	// TODO: Actor ������ unordered_map���� �ϴ°� �� ��������?, level���ٴ� world���� �����ϴ°� �����Ͱ���.
	// TODO: Level�� ������ ���̹Ƿ� level�� ���� Actor�� ���� �����ϴ°� ������ ����.
	// (��, World�� ���� actor�� level�� ���� actor�� �����°�?)
	// Layer���� ������ ������� Rendering (ex: background -> object, �̷��� object�� background���� ���δ�)
	std::vector<std::shared_ptr<Actor>> _actors[LT_MAXCOUNT]; // ���� 2D �����̶� �̷��� �� ��, 3D�� Depth������ Ȯ��
};

