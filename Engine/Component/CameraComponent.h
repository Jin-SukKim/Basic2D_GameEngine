#pragma once
#include "Component.h"

class CameraComponent : public Component
{
	GENERATE_BODY(CameraComponent, Component)
public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;
};

