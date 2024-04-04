#include "pch.h"
#include "Player.h"
#include "CameraComponent.h"
#include "Flipbook.h"
#include "InputManager.h" // TODO: manager보다는 InputComponent가 더 좋을것 같다

Player::Player()
{
	// Set texture/flipbook
	SetPlayerAnimation();

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

	if (_state == ActionState::AS_Attack) {
		if (IsAnimationEnded())
			SetState(ActionState::AS_Idle);
	}
	else
		PlayerInput();
	PlayerMove(DeltaTime);
	
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc); // Flipbook Actor에서 설정된 _flipbook을 렌더링
}

void Player::UpdateAnimation()
{
	switch (_state)
	{
	case ActionState::AS_Idle:
		SetFlipbook(_idle[_dir]);
		break;
	case ActionState::AS_Move:
		SetFlipbook(_move[_dir]);
		break;
	case ActionState::AS_Attack:
		SetFlipbook(_attack[_dir]);
		break;
	default:
		break;
	}
}

void Player::SetDir(Dir dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	// 방향이 바뀌면 Animation도 상태에 맞게 바꿔준다.
	UpdateAnimation();
}

void Player::SetState(ActionState state)
{
	if (_state == state)
		return;

	_state = state;
	// 상태가 바뀌면 Animation도 상태에 맞게 바꿔준다.
	UpdateAnimation();
}

void Player::SetPlayerAnimation()
{
	GET_SINGLE(AssetManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(AssetManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(AssetManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(AssetManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));

	// IDLE
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerUp")) {
		_idle[DIR_Up] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_IdleUp");
		_idle[DIR_Up]->SetInfo({ texture, L"FB_IdleUp", {200, 200}, 0, 9, 0, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerDown")) {
		_idle[DIR_Down] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_IdleDown");
		_idle[DIR_Down]->SetInfo({ texture, L"FB_IdleDown", {200, 200}, 0, 9, 0, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerLeft")) {
		_idle[DIR_Left] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_IdleLeft");
		_idle[DIR_Left]->SetInfo({ texture, L"FB_IdleLeft", {200, 200}, 0, 9, 0, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerRight")) {
		_idle[DIR_Right] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_IdleRight");
		_idle[DIR_Right]->SetInfo({ texture, L"FB_IdleRight", {200, 200}, 0, 9, 0, 0.5f });
	}

	// MOVE
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerUp")) {
		_move[DIR_Up] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_MoveUp");
		_move[DIR_Up]->SetInfo({ texture, L"FB_MoveUp", {200, 200}, 0, 9, 1, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerDown")) {
		_move[DIR_Down] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_MoveDown");
		_move[DIR_Down]->SetInfo({ texture, L"FB_MoveDown", {200, 200}, 0, 9, 1, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerLeft")) {
		_move[DIR_Left] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_MoveLeft");
		_move[DIR_Left]->SetInfo({ texture, L"FB_MoveLeft", {200, 200}, 0, 9, 1, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerRight")) {
		_move[DIR_Right] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_MoveRight");
		_move[DIR_Right]->SetInfo({ texture, L"FB_MoveRight", {200, 200}, 0, 9, 1, 0.5f });
	}

	// SKILL
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerUp")) {
		_attack[DIR_Up] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_AttackUp");
		_attack[DIR_Up]->SetInfo({ texture, L"FB_AttackUp", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerDown")) {
		_attack[DIR_Down] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_AttackDown");
		_attack[DIR_Down]->SetInfo({ texture, L"FB_AttackDown", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerLeft")) {
		_attack[DIR_Left] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_AttackLeft");
		_attack[DIR_Left]->SetInfo({ texture, L"FB_AttackLeft", {200, 200}, 0, 7, 3, 0.5f, false });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"PlayerRight")) {
		_attack[DIR_Right] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_AttackRight");
		_attack[DIR_Right]->SetInfo({ texture, L"FB_AttackRight", {200, 200}, 0, 7, 3, 0.5f, false });
	}
}

void Player::PlayerInput()
{
	// enum Dir과 순서를 맞춰준다. (상하좌우)
	static Vector2D nextDir[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // 다음 방향

	if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::W)) {
		SetDir(DIR_Up);
		SetSpeed(nextDir[DIR_Up] * _maxSpeed);
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::S)) {
		SetDir(DIR_Down);
		SetSpeed(nextDir[DIR_Down] * _maxSpeed);
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::A)) {
		SetDir(DIR_Left);
		SetSpeed(nextDir[DIR_Left] * _maxSpeed);
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::D)) {
		SetDir(DIR_Right);
		SetSpeed(nextDir[DIR_Right] * _maxSpeed);
	}
	else 
		SetSpeed(Vector2D::Zero);
	
	if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::SpaceBar)) 
		SetState(ActionState::AS_Attack);
}

void Player::PlayerMove(float DeltaTime)
{
	if (_state == ActionState::AS_Attack)
		return;

	if (_speed == Vector2D::Zero)
		SetState(ActionState::AS_Idle);
	else
		SetState(ActionState::AS_Move);

	SetPos(GetPos() + _speed * DeltaTime);
}


