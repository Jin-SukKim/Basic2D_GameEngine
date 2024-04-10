#pragma once
#include "Object.h"

class Component;

// TODO: Actor와 Component를 생성하는 클래스를 만들어 사용하는게 좋을것같다 (UE의 CreateDefaultSubobject 처럼)
// TODO: 만약 그렇다면 Actor와 Component들을 vector보다는 map으로 관리하는게 더 좋을수 있을것 같다
class Actor : public Object, public std::enable_shared_from_this<Actor>
{
	using Super = Object;
public:
	Actor(ObjectType type = ObjectType::Actor);
	virtual ~Actor();

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc);

	template<typename ReturnType>
	std::shared_ptr<ReturnType> CreateComponent(std::wstring name);
	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::weak_ptr<Component> component);

private:
	std::vector<std::shared_ptr<Component>> _components;
};

template<typename ReturnType>
inline std::shared_ptr<ReturnType> Actor::CreateComponent(std::wstring name)
{
	std::shared_ptr<ReturnType> component = std::make_shared<ReturnType>();
	component->SetName(name);
	AddComponent();
	return std::move(component);
}
