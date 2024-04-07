#pragma once
#include "Component.h"
#include "ColliderDelegate.h"

class SquareComponent;
class CircleComponent;
class Actor;

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

	// TODO: OnComponentBeginOverlap, EndOverlap과 연결될 Delegate Funciont도 만들기
	virtual void OnComponentBeginOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);
	virtual void OnComponentEndOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other);

protected:
	// TODO: 겹친 영역도 계산하기 https ://blog.naver.com/winterwolfs/10165506488
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

	// TODO: https://walbourn.github.io/modern-c++-bitmask-types/ : bit flag example
	// Bit flag좀 더 관리하기 쉽게 발전 (enum을 활용 ec: enum Type { type = 1u << 0, type2 = 0x01, type2 = 0x02, type2 = 0x04 };) , 1u = unsigned digit, 받기 uint myState = 0;
	// 누구랑 충돌할지
	uint8 _collisionFlag = ~0; // Default = 모두 충돌

	// 자신과 충돌한 Collider 추적 (이미 충돌한 Collider들은 충돌체크를 더 하지 않도록)
	std::unordered_set<std::shared_ptr<Collider>> _collisionSet;

	Vector2D _intersect = Vector2D::Zero;
};
