#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor(ObjectType type) : Super(type)
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
	for (auto comp : _components)
		comp->Init();
}

void Actor::Tick(float DeltaTime)
{
	for (auto comp : _components)
		comp->Tick(DeltaTime);
}

void Actor::Render(HDC hdc)
{
	for (auto comp : _components)
		comp->Render(hdc);
}

void Actor::AddComponent(const std::shared_ptr<Component>& component)
{
	if (component == nullptr)
		return;

	component->SetOwner(weak_from_this());
	_components.push_back(component);
}

void Actor::RemoveComponent(const std::shared_ptr<Component>& component)
{
	if (component == nullptr)
		return;

	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;

	_components.erase(findIt);
}
