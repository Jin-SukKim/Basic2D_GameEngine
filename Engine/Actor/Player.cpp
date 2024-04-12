#include "pch.h"
#include "Player.h"
#include "Component\CameraComponent.h"
#include "Component\SquareComponent.h"
#include "Resources\Flipbook.h"
#include "Resources\Tilemap.h"
#include "Manager\AssetManager.h"
#include "Manager\InputManager.h" // TODO: manager보다는 InputComponent가 더 좋을것 같다
#include "Actor\TilemapActor.h"
#include "World\Level.h"
#include "World\World.h"

Player::Player()
{
	Set2DAnimation();

	SetTag(L"Player");

	_camera = CreateSubobject<CameraComponent>(L"PlayerCamera");
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

	if (GetState() == ActionState::AS_Attack) {
		Attack(DeltaTime);
	}
	else
		PlayerInput();
	Move(DeltaTime);
	
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc); // Flipbook Actor에서 설정된 _flipbook을 렌더링
}

void Player::UpdateAnimation()
{
	switch (GetState())
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

void Player::Attack(float DeltaTime)
{
	Super::Attack(DeltaTime);

	if (IsAnimationStarted())
		_attackZone->SetCollisionEnable();
	else
		_attackZone->SetCollisionDisable();

	// 애니메이션이 끝나면 다음 공격 가능
	if (IsAnimationEnded()) {
		SetState(ActionState::AS_Idle);
	}
}


void Player::Set2DAnimation()
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


	SetState(ActionState::AS_Idle);
}

void Player::PlayerInput()
{
	if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::W)) {
		SetDir(DIR_Up);
		SetSpeed(GetMaxSpeed());
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::S)) {
		SetDir(DIR_Down);
		SetSpeed(GetMaxSpeed());
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::A)) {
		SetDir(DIR_Left);
		SetSpeed(GetMaxSpeed());
	}
	else if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::D)) {
		SetDir(DIR_Right);
		SetSpeed(GetMaxSpeed());
	}
	else 
		SetSpeed(0.f);
	
	if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::SpaceBar)) 
		SetState(ActionState::AS_Attack);
}

void Player::Move(float DeltaTime)
{
	if (GetState() == ActionState::AS_Attack)
		return;

	// 액터 크기만큼 보정
	std::shared_ptr<Tilemap> tilemap = Level::GetCurTilemap();
	Vector2D cellPos = GetPos() + GetDirVector2D(GetDir()) * (GetSize() * 0.5f);
	Vector2D toTilemapPos = Level::GetCurrentTilemapActor()->ConvertToTilemapPos(cellPos);
	if (tilemap && tilemap->CanGo(toTilemapPos) == false) {
		SetSpeed(0.f);
	}

	if (GetSpeed() == 0.f)
		SetState(ActionState::AS_Idle);
	else
		SetState(ActionState::AS_Move);

	SetPos(GetPos() + GetDirVector2D(GetDir()) * GetSpeed() * DeltaTime);
}


