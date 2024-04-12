#pragma once
#include "Component.h"
#include "ColliderDelegate.h"

class SquareComponent;
class CircleComponent;
class Actor;

/*
	TODO: Overlap�� Hit���� ����
		Ignore = �� Collider�� ���� �ƿ� �浹���� ������
		Overlap = �� Collider �� �ϳ��� bitflag�� Ű�� overlap (��, �ϳ��� �浹 �����ϸ�)
		Hit = �� Collider ��� ���� �浹�� �� ������ Hit
*/
class Collider : public Component, public std::enable_shared_from_this<Collider>
{
	GENERATE_BODY(Collider, Component)
public:
	Collider(ColliderType colliderType);

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void Clear() override;

	// TODO : �� Collider�� ���� �浹�Ұ��� Bit flag�� Ȱ���� �� �� ����ȭ
	virtual bool CheckCollision(std::weak_ptr<Collider> other);

	// �̹� �浹�ߴ���
	bool IsCollided(std::shared_ptr<Collider> other) {
		return _collisionSet.contains(other);
	}

	virtual void OnComponentBeginOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);
	virtual void OnComponentEndOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);

protected:
	// TODO: ��ģ ������ ����ϱ� https ://blog.naver.com/winterwolfs/10165506488
	bool CheckCollisionSquareToSqaure(std::weak_ptr<SquareComponent> b1, std::weak_ptr<SquareComponent> b2);
	bool CheckCollisionCircleToSquare(std::weak_ptr<CircleComponent> c1, std::weak_ptr<SquareComponent> b1);
	bool CheckCollisionCircleToCircle(std::weak_ptr<CircleComponent> c1, std::weak_ptr<CircleComponent> c2);

private:
	// ���� ���ȿ� �ִ��� Ȯ��
	bool CheckPointInCircle(const Vector2D& cPos, const float& radius, const Vector2D& point);

public:
	ColliderType GetColliderType() const { return _colliderType; }

	void SetShowDebug(bool show) { _showDebug = show; }

	void SetCollisionLayer(CollisionLayerType layer) { _collisionLayer = layer; }
	CollisionLayerType GetCollisionLayer() const { return _collisionLayer; }

	void SetCollisionFlag(uint8 flag) {	_collisionFlag = flag;	}
	uint8 GetCollisionFlag() const { return _collisionFlag;	}

	void ResetCollisionFlag() { _collisionFlag = 0; }
	void AddCollisionFlagLayer(CollisionLayerType layer);
	void RemoveCollisionFlagLayer(CollisionLayerType layer);

	void AddCollisionSet(std::shared_ptr<Collider> other) { _collisionSet.insert(other); }
	void RemoveCollisionSet(std::shared_ptr<Collider> other) { _collisionSet.erase(other); }

	void SetIntersect(Vector2D intersect) { _intersect = intersect;	}
	Vector2D GetIntersect() const { return _intersect; }

	void SetCollisionEnable() { _enable = true;	}
	void SetCollisionDisable() { _enable = false; }
	bool GetCollisionEnable() const {
		return _enable;
	}
public:
	// Collider Component�� owner object�� ������� Manager Ŭ�������� ���� ������� �����Ƿ�
	// raw pointer�� this�� ����ص� �� �� ����.
	Delegate _beginOverlapDelegate;
	Delegate _endOverlapDelegate;

private:
	ColliderType _colliderType; 
	bool _showDebug = true; 
	// TODO : �̰͵� bit flag�� �ϸ� �� ������?
	CollisionLayerType _collisionLayer = CLT_Object; // �ڽ��� �������� (ex: Player, Static, Dynamic etc)

	// ������ �浹����
	uint8 _collisionFlag = CLT_Object | CLT_Trace;

	// �ڽŰ� �浹�� Collider ���� (�̹� �浹�� Collider���� �浹üũ�� �� ���� �ʵ���)
	std::unordered_set<std::shared_ptr<Collider>> _collisionSet;

	Vector2D _intersect = Vector2D::Zero;

	bool _enable = true;
};