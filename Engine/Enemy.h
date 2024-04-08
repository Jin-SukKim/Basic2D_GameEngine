#pragma once
#include "FlipbookActor.h"

class SquareComponent;
class Collider;

class Enemy : public FlipbookActor
{
	GENERATE_BODY(Enemy, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);
	void EndOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);

	void OnDamaged(class std::weak_ptr<Actor> attacker);

protected:
	void UpdateAnimation();

private:
	void SetEnemyAnimation();
	void EnemyMove(float DeltaTime);

	void Chase();

	Dir GetLookAtDir(Vector2D pos);

	void FindPath(Vector2D pos, Vector2D targetPos, std::vector<Vector2D>& path);
public:
	void SetDir(Dir dir);
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }

	void SetSpeed(Vector2D speed) { _speed = speed; }
	Vector2D GetSpeed() const { return _speed; }

	void SetWaitSeconds(float seconds) { _waitSeconds = seconds; }
	float GetWaitSeconds() const { return _waitSeconds; }

	void SetMaxWaitSeconds(float seconds) { _maxWaitSeconds = seconds; }
	float GetMaxWaitSeconds() const { return _maxWaitSeconds; }
private:
	Dir _dir = DIR_Down;
	ActionState _state = ActionState::AS_Idle;

	std::shared_ptr<SquareComponent> _square;

	std::array<std::shared_ptr<Flipbook>, 4> _move;

	float _waitSeconds = 0.f;
	float _maxWaitSeconds = 1.f;

	std::weak_ptr<Actor> _target;

	Vector2D _speed = Vector2D::Zero;
	float _maxSpeed = 70.f;
};

