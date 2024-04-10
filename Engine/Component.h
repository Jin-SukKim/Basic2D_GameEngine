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
	std::shared_ptr<Actor> GetOwner() const { return _owner.lock(); } // ������ nullptr
	
protected:
	// weak_ptr : ���� ��ȯ���� �ذ�, �ӽ÷� ������(cache) ����Ҷ� ���
	std::weak_ptr<Actor> _owner;
};

