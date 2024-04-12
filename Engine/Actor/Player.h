#pragma once
#include "GameActor.h"

class CameraComponent;

// TODO : Input과 Animation을 Component로 따로 만드는게 더 좋지 않을까
class Player : public GameActor
{
	GENERATE_BODY(Player, GameActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void Set2DAnimation() override;
	virtual void UpdateAnimation() override;
	virtual void Move(float DeltaTime) override;
	virtual void Attack(float DeltaTime) override;

private:
	void PlayerInput();

private:
	std::shared_ptr<CameraComponent> _camera;
};

