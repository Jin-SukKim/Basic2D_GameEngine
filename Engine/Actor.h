#pragma once
#include "Object.h"
class Actor : public Object
{
	using Super = Object;
public:
	Actor(ObjectType type = ObjectType::Actor);
	virtual ~Actor();

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc);
};

