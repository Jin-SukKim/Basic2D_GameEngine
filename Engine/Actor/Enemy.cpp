#include "pch.h"
#include "Enemy.h"
#include "Component\SquareComponent.h"
#include "Component\CircleComponent.h"
#include "Manager\AssetManager.h"
#include "Resources\Flipbook.h"
#include "Resources\Tilemap.h"
#include "Actor\TilemapActor.h"
#include "World\World.h"
#include "World\Level.h"
#include "Utils\AlgorithmUtils.h"

Enemy::Enemy() {

	Set2DAnimation();

	_circle = std::make_shared<CircleComponent>();
	_circle->SetCollisionLayer(CLT_Trace);
	_circle->SetCollisionFlag(CLT_Object);
	_circle->SetRadius(70.f);
	AddComponent(_circle);

	SetMaxSpeed(60.f);
}

Enemy::~Enemy() {}

void Enemy::Init()
{
	Super::Init();

	_circle->_endOverlapDelegate.BindDelegate(this, &Enemy::EndAttackRange);
}

void Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (GetState())
	{
	case ActionState::AS_Idle:
		Chase();
		break;
	case ActionState::AS_Move:
		Move(DeltaTime);
		break;
	case ActionState::AS_Attack:
		Attack(DeltaTime);
		break;
	}
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}


void Enemy::EndAttackRange(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	Chase();
}


void Enemy::UpdateAnimation()
{
	SetFlipbook(_move[_dir]);
}

void Enemy::Set2DAnimation()
{
	GET_SINGLE(AssetManager)->LoadTexture(L"Snake", L"Sprite\\Monster\\Snake.bmp", RGB(128, 128, 128));
	// Move
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"Snake")) {
		_move[DIR_Up] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_SnakeUp");
		_move[DIR_Up]->SetInfo({ texture, L"FB_SnakeUp", {100, 100}, 0, 3, 3, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"Snake")) {
		_move[DIR_Down] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_SnakeDown");
		_move[DIR_Down]->SetInfo({ texture, L"FB_SnakeDown", {100, 100}, 0, 3, 0, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"Snake")) {
		_move[DIR_Left] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_SnakeLeft");
		_move[DIR_Left]->SetInfo({ texture, L"FB_SnakeLeft", {100, 100}, 0, 3, 2, 0.5f });
	}
	if (std::shared_ptr<Texture> texture = GET_SINGLE(AssetManager)->GetTexture(L"Snake")) {
		_move[DIR_Right] = GET_SINGLE(AssetManager)->CreateFlipbook(L"FB_SnakeRight");
		_move[DIR_Right]->SetInfo({ texture, L"FB_SnakeRight", {100, 100}, 0, 3, 1, 0.5f });
	}


	SetState(ActionState::AS_Idle);
}

void Enemy::Move(float DeltaTime)
{
	Vector2D dir = (GetDestPos() - GetPos());
	float dist = dir.Length();
	if (dir.Length() < 5.f) // 도착지점에 충분히 가까우면
	{
		SetPos(GetDestPos());
		SetSpeed(0.f);
		SetState(ActionState::AS_Idle);
	}
	// 도착지까지 부드럽게 움직이도록 보정
	else {
		bool horizontal = std::abs(dir.X) > abs(dir.Y);
		if (horizontal)
			SetDir(dir.X < 0 ? DIR_Left : DIR_Right);
		else
			SetDir(dir.Y < 0 ? DIR_Up : DIR_Down);

		SetPos(GetPos() + GetDirVector2D(GetDir()) * GetSpeed() * DeltaTime);
	}
}

void Enemy::Chase()
{
	std::shared_ptr<TilemapActor> tmActor = Level::GetCurrentTilemapActor();
	if (tmActor == nullptr)
		return;

	std::shared_ptr<Actor> target = _target.lock();
	if (target == nullptr) {
		target = World::GetCurrentLevel()->FindClosestTarget(GetPos());
		SetCellPos(tmActor->ConvertToTilemapPos(GetPos()));
	}

	if (target) {
		Vector2D dir = target->GetPos() - GetPos();
		float dist = std::abs(dir.X) + std::abs(dir.Y);
		if (dist < 80.f) // 바로 앞이라면
		{
			SetDir(GetLookAtDir(target->GetPos()));
			SetWaitSeconds(GetMaxWaitSeconds());
			SetState(ActionState::AS_Attack);
		}
		else 
		{
			// 목표까지 길을 찾고 1칸 이동하고 다시 찾는 걸 반복
			// (계산량에 부담은 되나 더 자연스럽다. 부담되면 일정 시간에 찾도록 변경)
			std::vector<Vector2D> path;
			Vector2D targetCellPos = tmActor->ConvertToTilemapPos(target->GetPos());
			AlgorithmUtils::FindPathAStar(GetCellPos(), targetCellPos, OUT path);
			{
				// index 0은 현재 위치
				if (path.size() > 1)
				{
					Vector2D nextPos = path[1];
					if (tmActor->GetTilemap()->CanGo(nextPos))
					{
 						SetCellPos(nextPos);
						SetSpeed(GetMaxSpeed());
						SetState(ActionState::AS_Move);
					}
				}
				else 
					SetCellPos(GetCellPos());
			}
		}
	}
}

void Enemy::Attack(float DeltaTime)
{
	Super::Attack(DeltaTime);

	if (_waitSeconds > 0)
	{
		SetWaitSeconds(max(0, _waitSeconds - DeltaTime));
		_attackZone->SetCollisionDisable();
		return;
	}

	_attackZone->SetCollisionEnable();
	SetState(ActionState::AS_Idle);
}