#include "pch.h"
#include "Player.h"
#include "CameraComponent.h"
#include "Flipbook.h"
#include "InputManager.h" // TODO: manager보다는 InputComponent가 더 좋을것 같다
#include "SquareComponent.h"
#include "Level.h"
#include "Tilemap.h"
#include "World.h"
#include "SpriteEffect.h"

Player::Player()
{
	SetTag(L"Player");

	// Set texture/flipbook
	SetPlayerAnimation();

	_square = std::make_shared<SquareComponent>();
	_square->SetSize({ 50.f, 50.f });
	AddComponent(_square);

	_camera = std::make_shared<CameraComponent>();
	AddComponent(_camera);

	_attackBox = std::make_shared<SquareComponent>();
	_attackBox->AddLocalPos(GetDirVector2D(GetDir()) * 50.f);
	_attackBox->SetSize({ 25.f, 25.f });
	_attackBox->SetCollisionLayer(CLT_Trace);
	_attackBox->SetCollisionFlag(CLT_Object);
	_attackBox->SetCollisionDisable();
	AddComponent(_attackBox);


	// Effect
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"HitEffect"))
	{
		_hitEffect = std::make_shared<SpriteEffect>();
		_hitEffect->SetFlipbook(GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_Hit"));
		_hitEffect->SetInfo({ texture, L"FB_Hit", {50, 47}, 0, 5, 0, 0.5f, false });
	}
}

Player::~Player()
{
}

void Player::Init()
{
	Super::Init();

	_square->_beginOverlapDelegate.BindDelegate(this, &Player::BeginOverlapFunction);
	_attackBox->_beginOverlapDelegate.BindDelegate(this, &Player::BeginAttackBox);
}

void Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_state == ActionState::AS_Attack) {
		Attack();
	}
	else
		PlayerInput();
	PlayerMove(DeltaTime);
	
}

void Player::Render(HDC hdc)
{
	Super::Render(hdc); // Flipbook Actor에서 설정된 _flipbook을 렌더링
}

void Player::BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	std::shared_ptr<Collider> collider = dynamic_pointer_cast<SquareComponent>(comp.lock());
	if (collider)
		SetPos(GetPos() - collider->GetIntersect());
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

Vector2D Player::GetDirVector2D(Dir dir)
{
	// enum Dir과 순서를 맞춰준다. (상하좌우)
	static Vector2D nextDir[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // 다음 방향
	return nextDir[dir];
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
	GET_SINGLE(AssetManager)->LoadTexture(L"HitEffect", L"Sprite\\Effect\\Hit.bmp", RGB(0, 0, 0));

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

void Player::PlayerMove(float DeltaTime)
{
	if (_state == ActionState::AS_Attack)
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

void Player::Attack()
{
	if (GetFlipbook() == nullptr)
		return;

	_attackBox->SetCollisionEnable();
	_attackBox->AddLocalPos(GetDirVector2D(GetDir()) * 50.f);
	
	// 애니메이션이 끝나면 다음 공격 가능
	if (IsAnimationEnded()) {
		_attackBox->SetCollisionDisable();
		SetState(ActionState::AS_Idle);
	}
}

void Player::BeginAttackBox(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	if (shared_from_this() == other.lock())
		return;

	// 따로 weapon actor를 사용하면 damageCauser parameter는 무기 액터
	ApplyDamage(other, _playerStat.attack, weak_from_this(), weak_from_this());

	std::shared_ptr<Level> level = World::GetCurrentLevel();
	if (level == nullptr)
		return;

	if (_hitEffect) {
		_hitEffect = level->SpawnObject<SpriteEffect>(_hitEffect, GetPos() + GetDirVector2D(GetDir()) * 50.f);
	}

}


