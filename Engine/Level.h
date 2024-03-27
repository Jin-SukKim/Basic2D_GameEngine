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

public:
	// Layer별로 저장해 순서대로 Rendering (ex: background -> object, 이래야 object가 background위에 보인다)
	std::vector<std::shared_ptr<Actor>> _actors[LT_MAXCOUNT]; // 현재 2D 엔진이라 이렇게 한 것, 3D면 Depth값으로 확인
};

