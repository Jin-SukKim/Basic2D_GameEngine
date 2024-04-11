#pragma once
#include "Component.h"
#include "ColliderDelegate.h"

class SquareComponent;
class CircleComponent;
class Actor;

/*
	TODO: Overlap와 Hit으로 구분
		Ignore = 두 Collider가 서로 아예 충돌하지 않으면
		Overlap = 두 Collider 중 하나만 bitflag를 키면 overlap (즉, 하나만 충돌 가능하면)
		Hit = 두 Collider 모두 서로 충돌할 수 있으면 Hit
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

	// TODO : 두 Collider가 서로 충돌할건지 Bit flag를 활용해 좀 더 최적화
	virtual bool CheckCollision(std::weak_ptr<Collider> other);

	// 이미 충돌했는지
	bool IsCollided(std::shared_ptr<Collider> other) {
		return _collisionSet.contains(other);
	}

	virtual void OnComponentBeginOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);
	virtual void OnComponentEndOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);

protected:
	// TODO: 겹친 영역도 계산하기 https ://blog.naver.com/winterwolfs/10165506488
	bool CheckCollisionSquareToSqaure(std::weak_ptr<SquareComponent> b1, std::weak_ptr<SquareComponent> b2);
	bool CheckCollisionCircleToSquare(std::weak_ptr<CircleComponent> c1, std::weak_ptr<SquareComponent> b1);
	bool CheckCollisionCircleToCircle(std::weak_ptr<CircleComponent> c1, std::weak_ptr<CircleComponent> c2);

private:
	// 점이 원안에 있는지 확인
	bool CheckPointInCircle(const Vector2D& cPos, const Vector2D& radius, const Vector2D& point);

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

	void AddCollisionSet(std::shared_ptr<Collider> other) { _collisionSet.insert(other); }
	void RemoveCollisionSet(std::shared_ptr<Collider> other) { _collisionSet.erase(other); }

	void SetIntersect(Vector2D intersect) { _intersect = intersect;	}
	Vector2D GetIntersect() const { return _intersect; }
public:
	// Collider Component는 owner object가 사라질때 Manager 클래스에서 같이 사라지게 했으므로
	// raw pointer인 this를 사용해도 될 것 같다.
	Delegate _beginOverlapDelegate;
	Delegate _endOverlapDelegate;

private:
	ColliderType _colliderType; 
	bool _showDebug = true; 
	// TODO : 이것도 bit flag로 하면 더 좋을까?
	CollisionLayerType _collisionLayer = CLT_Object; // 자신이 무엇인지 (ex: Player, Static, Dynamic etc)

	// 누구랑 충돌할지
	uint8 _collisionFlag = CLT_Object | CLT_Trace;

	// 자신과 충돌한 Collider 추적 (이미 충돌한 Collider들은 충돌체크를 더 하지 않도록)
	std::unordered_set<std::shared_ptr<Collider>> _collisionSet;

	Vector2D _intersect = Vector2D::Zero;
};
