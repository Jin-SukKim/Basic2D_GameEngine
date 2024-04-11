#include "pch.h"
#include "Component.h"
#include "Actor.h"

Component::Component(ObjectType type) : Super(type)
{
}

Component::~Component()
{
}

void Component::Tick(float DeltaTime)
{
	std::shared_ptr<Actor> owner = _owner.lock();
	if (owner)
		SetPos(owner->GetPos() + _compPos);
}
