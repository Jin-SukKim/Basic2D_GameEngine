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
	std::shared_ptr<Actor> owner = GetOwner();
	if (owner)
		SetPos(owner->GetPos() + _compPos);
}

Vector2D Component::GetPos() const
{
	std::shared_ptr<Actor> owner = GetOwner();
	if (owner)
		return owner->GetPos() + _compPos;
	
	return _compPos;
}
