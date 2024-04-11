#pragma once
#include "Object.h"

class Actor;

class Component : public Object
{
	using Super = Object;
public:
	Component(ObjectType type = ObjectType::Component);
	virtual ~Component();

	virtual void Init() {};
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc) {};

	virtual void Clear() {};

public: // Getter/Setter
	void SetOwner(std::weak_ptr<Actor> owner) { _owner = owner; }
	std::shared_ptr<Actor> GetOwner() const { return _owner.lock(); } // 없으면 nullptr
	
	void AddLocalPos(const Vector2D& pos) { _compPos = pos; }

protected:
	// weak_ptr : 보통 순환문제 해결, 임시로 데이터(cache) 사용할때 사용
	std::weak_ptr<Actor> _owner;

	Vector2D _compPos = { 0.f, 0.f };
};

