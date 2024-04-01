#pragma once
#include "Object.h"

class Actor;

class Component : public Object
{
	using Super = Object;
public:
	Component(ObjectType type = ObjectType::Component);
	virtual ~Component();

	virtual void Init() = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void Render(HDC hdc) = 0;

public: // Getter/Setter
	void SetOwner(std::weak_ptr<Actor> owner) { _owner = owner; }
	std::shared_ptr<Actor> GetOwner() const { return _owner.lock(); } // 없으면 nullptr
	
protected:
	// weak_ptr : 보통 순환문제 해결, 임시로 데이터(cache) 사용할때 사용
	std::weak_ptr<Actor> _owner;
};

