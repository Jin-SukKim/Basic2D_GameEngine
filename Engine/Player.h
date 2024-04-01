#pragma once
#include "FlipbookActor.h"

class CameraComponent;

class Player : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

protected:
	// state ±â¹Ý
	void TickIdle();
	void TickMove();
	void TickAttack();

	void UpdateAnimation();

public:
	void SetDir(Dir dir) { _dir = dir; }
	Dir GetDir() const { return _dir; }

	void SetState(ActionState state);
	ActionState GetState() const { return _state; }

private:
	Dir _dir = DIR_Down;
	ActionState _state = ActionState::AS_Idle;

	std::shared_ptr<CameraComponent> _camera;
};

