#pragma once
#include "Component.h"

class SquareComponent;
class CircleComponent;

class Collider : public Component
{
	GENERATE_BODY(Collider, Component)
public:
	Collider(ColliderType colliderType);

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	// TODO : �� Collider�� ���� �浹�Ұ��� Bit flag�� Ȱ���� �� �� ����ȭ
	virtual bool CheckCollision(std::weak_ptr<Collider> other);

	// TODO: OnComponentBeginOverlap, EndOverlap�� ����� Delegate Funciont�� �����
protected:
	bool CheckCollisionSquareToSqaure(std::weak_ptr<SquareComponent> b1, std::weak_ptr<SquareComponent> b2);
	bool CheckCollisionCircleToSquare(std::weak_ptr<CircleComponent> c1, std::weak_ptr<SquareComponent> b1);
	bool CheckCollisionCircleToCircle(std::weak_ptr<CircleComponent> c1, std::weak_ptr<CircleComponent> c2);

public:
	void SetColliderType(ColliderType& colliderType) { _colliderType = colliderType; }
	ColliderType GetColliderType() const { return _colliderType; }

	void SetShowDebug(bool show) { _showDebug = show; }

	void SetCollisionLayer(CollisionLayerType layer) { _collisionLayer = layer; }
	CollisionLayerType GetCollisionLayer() const { return _collisionLayer; }

	void SetCollisionFlag(uint8 flag) {	_collisionFlag = flag;	}
	uint8 GetCollisionFlag() const { return _collisionFlag;	}

	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(CollisionLayerType layer);
	void RemoveCollisionFlagLayer(CollisionLayerType layer);
private:
	ColliderType _colliderType; 
	bool _showDebug = true; 
	// TODO : �̰͵� bit flag�� �ϸ� �� ������?
	CollisionLayerType _collisionLayer = CLT_Object; // �ڽ��� �������� (ex: Player, Static, Dynamic etc)

	// TODO: https://walbourn.github.io/modern-c++-bitmask-types/ : bit flag example
	// Bit flag�� �� �����ϱ� ���� ���� (enum�� Ȱ�� ec: enum Type { type = 1u << 0, type2 = 0x01, type2 = 0x02, type2 = 0x04 };) , 1u = unsigned digit, �ޱ� uint myState = 0;
	// ������ �浹����
	uint8 _collisionFlag = ~0; // Default = ��� �浹

	// �ڽŰ� �浹�� Collider ���� (�̹� �浹�� Collider���� �浹üũ�� �� ���� �ʵ���)
	std::unordered_set<std::shared_ptr<Collider>> _collisionSet;

};

