#include "pch.h"
#include "GameActor.h"
#include "Component\SquareComponent.h"
#include "SpriteEffect.h"
#include "Resources\Flipbook.h"
#include "Manager\AssetManager.h"
#include "Actor\TilemapActor.h"
#include "World\World.h"
#include "World\Level.h"

GameActor::GameActor() {

	Set2DAnimation();

	_actor = CreateSubobject<SquareComponent>(L"2DActor");
	_actor->SetSize({ 50.f, 50.f });
	AddComponent(_actor);

	_attackZone = CreateSubobject<SquareComponent>(L"AttackZone");
	_attackZone->SetSize({ 25.f, 25.f });
	_attackZone->AddLocalPos(GetDirVector2D(GetDir()) * 50.f);
	_attackZone->SetCollisionLayer(CLT_Trace);
	_attackZone->SetCollisionFlag(CLT_Object);
	_attackZone->SetCollisionDisable();
	AddComponent(_attackZone);

	// Effect 
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"HitEffect"))
	{
		_hitEffect = CreateSubobject<SpriteEffect>(L"HitEffect");
		_hitEffect->SetFlipbook(GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_Hit"));
		_hitEffect->SetInfo({ texture, L"FB_Hit", {50, 47}, 0, 5, 0, 0.5f, false });
	}
}

GameActor::~GameActor() {}

void GameActor::Init()
{
	Super::Init();

	_actor->_beginOverlapDelegate.BindDelegate(this, &GameActor::BeginOverlapFunction);
	_attackZone->_beginOverlapDelegate.BindDelegate(this, &GameActor::BeginAttackZone);
}

void GameActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void GameActor::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameActor::BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	std::shared_ptr<Collider> collider = dynamic_pointer_cast<SquareComponent>(comp.lock());
	if (collider)
		SetPos(GetPos() - collider->GetIntersect());
}

void GameActor::BeginAttackZone(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	// 따로 weapon actor를 사용하면 damageCauser parameter는 무기 액터
	ApplyDamage(other, _stat.attack, weak_from_this(), weak_from_this());

	std::shared_ptr<Level> level = World::GetCurrentLevel();
	if (level == nullptr)
		return;

	if (_hitEffect) {
		_hitEffect = level->SpawnObject<SpriteEffect>(_hitEffect, GetPos() + GetDirVector2D(GetDir()) * 50.f);
	}
}

float GameActor::TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser)
{
	float damage = Super::TakeDamage(damageAmount, eventInstigator, damageCauser);

	GetDamage(damage);

	return damage;
}

void GameActor::Set2DAnimation()
{
	GET_SINGLE(AssetManager)->LoadTexture(L"HitEffect", L"Sprite\\Effect\\Hit.bmp", RGB(0, 0, 0));

}

void GameActor::Attack(float DeltaTime)
{
	if (GetFlipbook() == nullptr)
		return;
}

void GameActor::GetDamage(float damage)
{
	damage -= _stat.defence;
	if (damage <= 0)
		return;

	_stat.hp = max(0.f, _stat.hp - damage);
	if (_stat.hp == 0.f)
	{
		std::shared_ptr<Level> level = World::GetCurrentLevel();
		if (level)
			level->RemoveActor(weak_from_this());
	}
}

Dir GameActor::GetLookAtDir(Vector2D pos)
{
	Vector2D dir = pos - GetPos();
	if (dir.X > 0)
		return DIR_Right;
	else if (dir.X < 0)
		return DIR_Left;
	else if (dir.Y > 0)
		return DIR_Down;
	else
		return DIR_Up;
}

Vector2D GameActor::GetDirVector2D(Dir dir)
{
	// enum Dir과 순서를 맞춰준다. (상하좌우)
	static Vector2D nextDir[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // 다음 방향
	return nextDir[dir];
}

void GameActor::SetDir(Dir dir)
{
	if (_dir == dir)
		return;

	_dir = dir;

	_attackZone->AddLocalPos(GetDirVector2D(_dir) * 50.f);
	// 방향이 바뀌면 Animation도 상태에 맞게 바꿔준다.
	UpdateAnimation();
}

void GameActor::SetState(ActionState state)
{
	if (_state == state)
		return;

	_state = state;
	// 상태가 바뀌면 Animation도 상태에 맞게 바꿔준다.
	UpdateAnimation();
}

void GameActor::SetCellPos(const Vector2D& cellPos)
{
	_cellPos = cellPos;

	std::shared_ptr<TilemapActor> tmActor = Level::GetCurrentTilemapActor();
	if (tmActor == nullptr)
		return;

	SetDestPos(tmActor->GetCellPos(cellPos));
}
