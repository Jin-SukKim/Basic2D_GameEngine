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

	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::weak_ptr<Component> component);

	// TODO: Damage 관련 함수
	// https://erikanes.tistory.com/352
	// https://mingyu0403.tistory.com/258
	// parameter: 데미지를 입은 액터, 데미지, 데미지를 준 액터(플레이어 등), 데미지를 준 실직적 액터(총알, 칼 등),
	void ApplyDamage(std::weak_ptr<Actor> damagedActor, float damage, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser);
	virtual float TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser);
private:
	std::vector<std::shared_ptr<Component>> _components;
};
