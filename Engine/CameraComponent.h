#pragma once
#include "Component.h"

class CameraComponent : public Component
{
	using Super = Component;
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;
};

