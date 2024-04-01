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

void Actor::AddComponent(std::shared_ptr<Component> component)
{
	if (component == nullptr)
		return;
	
	// 부모 클래스 가르킬땐 static_pointer_cast
	// 자식 클래스 또는 다른 클래스를 가르킬땐 dynamic_pointer_cast
	component->SetOwner(std::dynamic_pointer_cast<Actor>(shared_from_this()));
	_components.push_back(std::move(component));
}

void Actor::RemoveComponent(std::weak_ptr<Component> component)
{
	std::shared_ptr<Component> comp = component.lock();
	if (comp == nullptr)
		return;

	auto findIt = std::find(_components.begin(), _components.end(), comp);
	if (findIt == _components.end())
		return;

	_components.erase(findIt);
}
