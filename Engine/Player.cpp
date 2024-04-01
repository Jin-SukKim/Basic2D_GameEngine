#include "pch.h"
#include "Player.h"
#include "CameraComponent.h"

Player::Player()
{
	_camera = std::make_shared<CameraComponent>();
	AddComponent(_camera);
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (_state)
	{
	case ActionState::AS_Idle:
		TickIdle();
		break;
	case ActionState::AS_Move:
		TickMove();
		break;
	case ActionState::AS_Attack:
		break;
	default:
		TickAttack();
		break;
	}
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Player::TickIdle()
{
}

void Player::TickMove()
{
}

void Player::TickAttack()
{
}

void Player::UpdateAnimation()
{
}

void Player::SetState(ActionState state)
{
}
