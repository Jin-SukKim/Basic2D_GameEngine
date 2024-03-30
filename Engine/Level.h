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
	virtual void RemoveActor(std::shared_ptr<Actor> actor);

	int32 GetActorCount();

public:
	// TODO: Actor ������ unordered_map���� �ϴ°� �� ��������?
	// Layer���� ������ ������� Rendering (ex: background -> object, �̷��� object�� background���� ���δ�)
	std::vector<std::shared_ptr<Actor>> _actors[LT_MAXCOUNT]; // ���� 2D �����̶� �̷��� �� ��, 3D�� Depth������ Ȯ��
};

