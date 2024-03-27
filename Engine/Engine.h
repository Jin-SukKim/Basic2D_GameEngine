#pragma once
#include "EngineWindow.h"

class World;

class Engine : public EngineWindow
{
	using Super = EngineWindow;

public:
	Engine();
	virtual ~Engine();

	virtual bool Init() override;
	virtual void Tick() override;
	virtual void Render() override;

	Engine& GetEngine() { return *this; }
private:
	std::unique_ptr<World> _world;
};

