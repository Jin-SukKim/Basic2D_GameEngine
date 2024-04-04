#pragma once
#include "FlipbookActor.h"

class CameraComponent;

class Player : public FlipbookActor
{
	GENERATE_BODY(Player, FlipbookActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

protected:
	void UpdateAnimation();

public:
	void SetDir(Dir dir);
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }
private:
	void SetPlayerAnimation();
	void PlayerInput();

public:
	void SetSpeed(Vector2D speed) { _speed = speed; }
	Vector2D GetSpeed() const { return _speed; }
	void PlayerMove(float DeltaTime);
private:
	Dir _dir = DIR_Down;
	ActionState _state;

	std::shared_ptr<CameraComponent> _camera;

	std::array<std::shared_ptr<Flipbook>, 4> _idle;
	std::array<std::shared_ptr<Flipbook>, 4> _move;
	std::array<std::shared_ptr<Flipbook>, 4> _attack;

	bool _keyPressed = false;

	Vector2D _speed = Vector2D::Zero;
	float _maxSpeed = 100.f;
};

