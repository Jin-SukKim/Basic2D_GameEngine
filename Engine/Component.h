#pragma once
#include "Object.h"

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
	void SetOwner(std::weak_ptr<Object> owner) { _owner = owner; }
	std::shared_ptr<Object> GetOwner() { return _owner.lock(); } // ¾øÀ¸¸é nullptr
	
protected:
	std::weak_ptr<Object> _owner;
};

