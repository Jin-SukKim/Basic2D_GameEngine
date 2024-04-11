#pragma once
#include "FlipbookActor.h"
#include "Stat.h"

class SquareComponent;
class CircleComponent;
class Collider;
class SpriteEffect;

class Enemy : public FlipbookActor
{
	GENERATE_BODY(Enemy, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);
	void BeginAttackRange(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);
	void EndAttackRange(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);

	virtual float TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser) override;
protected:
	void UpdateAnimation();

private:
	void SetEnemyAnimation();
	void EnemyMove(float DeltaTime);

	void Chase();
	void Attack(float DeltaTime);

	Dir GetLookAtDir(Vector2D pos);

	Vector2D GetDirVector2D(Dir dir);
	
	void GetDamage(float damage);
public:
	void SetCellPos(const Vector2D& cellPos);
	Vector2D GetCellPos() const { return _cellPos; }

	void SetDestPos(const Vector2D& pos) { _destPos = pos; }
	Vector2D GetDestPos() const { return _destPos; }

	void SetDir(Dir dir);
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }

	void SetSpeed(float speed) { _enemyStat.speed = speed; }
	float GetSpeed() const { return _enemyStat.speed; }

	void SetMaxSpeed(float speed) { _enemyStat.maxSpeed = speed; }
	float GetMaxSpeed() const { return _enemyStat.maxSpeed; }

	void SetWaitSeconds(float seconds) { _waitSeconds = seconds; }
	float GetWaitSeconds() const { return _waitSeconds; }

	void SetMaxWaitSeconds(float seconds) { _maxWaitSeconds = seconds; }
	float GetMaxWaitSeconds() const { return _maxWaitSeconds; }
private:
	Dir _dir = DIR_Left;
	ActionState _state;

	std::shared_ptr<SquareComponent> _square;
	std::shared_ptr<CircleComponent> _circle;
	std::shared_ptr<CircleComponent> _attackZone;

	std::array<std::shared_ptr<Flipbook>, 4> _move;

	std::shared_ptr<SpriteEffect> _hitEffect;

	Vector2D _cellPos;
	Vector2D _destPos;

	float _waitSeconds = 0.f;
	float _maxWaitSeconds = 1.f;

	std::weak_ptr<Actor> _target;

	Stat _enemyStat;
};

