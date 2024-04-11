#include "pch.h"
#include "Actor.h"
#include "Component.h"

Actor::Actor(ObjectType type) : Super(type)
{
}

Actor::~Actor()
{
	for (auto comp : _components)
		comp->Clear();
}

void Actor::Init()
{
	for (auto comp : _components) {

		// 부모 클래스 가르킬땐 static_pointer_cast
		// 자식 클래스 또는 다른 클래스를 가르킬땐 dynamic_pointer_cast
		comp->SetOwner(weak_from_this());
		comp->Init();
	}
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

void Actor::ApplyDamage(std::weak_ptr<Actor> damagedActor, float damage, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser)
{
	std::shared_ptr<Actor> attacker = eventInstigator.lock();
	std::shared_ptr<Actor> causer = damageCauser.lock();
	std::shared_ptr<Actor> actor = damagedActor.lock();
	if (attacker == nullptr || causer == nullptr || actor == nullptr)
		return;

	actor->TakeDamage(damage, eventInstigator, damageCauser);
}

float Actor::TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser)
{
	std::shared_ptr<Actor> attacker = eventInstigator.lock();
	std::shared_ptr<Actor> causer = damageCauser.lock();
	if (attacker == nullptr || causer == nullptr)
		return 0.0f;

	return damageAmount;
}
