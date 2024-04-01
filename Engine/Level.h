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
	// TODO: Actor 관리는 unordered_map으로 하는게 더 좋을수도?, level보다는 world에서 관리하는게 맞을것같다.
	// TODO: Level은 일종의 맵이므로 level에 속한 Actor를 따로 관리하는게 좋을것 같다.
	// (즉, World에 속한 actor와 level에 속한 actor로 나누는것?)
	// Layer별로 저장해 순서대로 Rendering (ex: background -> object, 이래야 object가 background위에 보인다)
	std::vector<std::shared_ptr<Actor>> _actors[LT_MAXCOUNT]; // 현재 2D 엔진이라 이렇게 한 것, 3D면 Depth값으로 확인
};

