#pragma once
class World
{
public:
	World();
	~World();

	void Init();
	void Tick();
	void Render(HDC hdc);

};

