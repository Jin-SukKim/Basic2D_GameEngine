#pragma once
#include "FlipbookActor.h"
#include "Stat.h"

class CameraComponent;
class SquareComponent;
class Collider;
class SpriteEffect;

// TODO : Input과 Animation을 Component로 따로 만드는게 더 좋지 않을까
class Player : public FlipbookActor
{
	GENERATE_BODY(Player, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;
	
	void BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);
	void Attack();
	void BeginAttackBox(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);

protected:
	void UpdateAnimation();

private:
	void SetPlayerAnimation();
	void PlayerInput();
	Vector2D GetDirVector2D(Dir dir);
	void PlayerMove(float DeltaTime);

public:
	void SetDir(Dir dir);
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }

	void SetSpeed(float speed) { _playerStat.speed = speed; }
	float GetSpeed() const { return _playerStat.speed; }
	
	void SetMaxSpeed(float speed) { _playerStat.maxSpeed = speed; }
	float GetMaxSpeed() const { return _playerStat.maxSpeed; }

private:
	Dir _dir = DIR_Down;
	ActionState _state;

	std::shared_ptr<SquareComponent> _square;
	std::shared_ptr<CameraComponent> _camera;
	std::shared_ptr<SquareComponent> _attackBox;

	std::array<std::shared_ptr<Flipbook>, 4> _idle;
	std::array<std::shared_ptr<Flipbook>, 4> _move;
	std::array<std::shared_ptr<Flipbook>, 4> _attack;

	std::shared_ptr<SpriteEffect> _hitEffect;

	bool _keyPressed = false;

	Stat _playerStat;
};

