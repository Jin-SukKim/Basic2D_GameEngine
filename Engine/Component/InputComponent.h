#pragma once
#include "Component.h"
class InputComponent : public Component
{
	GENERATE_BODY(InputComponent, Component)
public:

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	/*
		TODO:
			InputAction = 
			InputType = down, press, up
			object,
			function ptr
	*/ 

};

