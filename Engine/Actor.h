#pragma once
#include "Object.h"

class Component;

// TODO: Actor�� Component�� �����ϴ� Ŭ������ ����� ����ϴ°� �����Ͱ��� (UE�� CreateDefaultSubobject ó��)
// TODO: ���� �׷��ٸ� Actor�� Component���� vector���ٴ� map���� �����ϴ°� �� ������ ������ ����
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

	// TODO: Damage ���� �Լ�
	// https://erikanes.tistory.com/352
	// https://mingyu0403.tistory.com/258
	// parameter: �������� ���� ����, ������, �������� �� ����(�÷��̾� ��), �������� �� ������ ����(�Ѿ�, Į ��),
	void ApplyDamage(std::weak_ptr<Actor> damagedActor, float damage, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser);
	virtual float TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser);
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
