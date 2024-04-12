#pragma once
#include "FlipbookActor.h"
#include "Stat.h"

class SquareComponent;
class SpriteEffect;
class Collider;

class GameActor : public FlipbookActor
{
	GENERATE_BODY(GameActor, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);
	void BeginAttackZone(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);

	virtual float TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser) override;

protected:
	virtual void Set2DAnimation();
	virtual void UpdateAnimation() {}
	virtual void Attack(float DeltaTime);
	virtual void GetDamage(float damage);
	
	virtual Dir GetLookAtDir(Vector2D pos);
	virtual Vector2D GetDirVector2D(Dir dir);

	virtual void Move(float DeltaTime) {}
public:
	void SetDir(Dir dir);
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }

	void SetSpeed(float speed) { _stat.speed = speed; }
	float GetSpeed() const { return _stat.speed; }

	void SetMaxSpeed(float speed) { _stat.maxSpeed = speed; }
	float GetMaxSpeed() const { return _stat.maxSpeed; }

	void SetCellPos(const Vector2D& cellPos);
	Vector2D GetCellPos() const { return _cellPos; }

	void SetDestPos(const Vector2D& pos) { _destPos = pos; }
	Vector2D GetDestPos() const { return _destPos; }

protected:
	Dir _dir = DIR_Down;
	ActionState _state = ActionState::AS_Attack;

	std::shared_ptr<SquareComponent> _actor;
	std::shared_ptr<SquareComponent> _attackZone;

	std::array<std::shared_ptr<Flipbook>, 4> _idle;
	std::array<std::shared_ptr<Flipbook>, 4> _move;
	std::array<std::shared_ptr<Flipbook>, 4> _attack;

	std::shared_ptr<SpriteEffect> _hitEffect;

	Vector2D _cellPos;
	Vector2D _destPos;

	Stat _stat;
};

