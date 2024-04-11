#include "pch.h"
#include "Enemy.h"
#include "SquareComponent.h"
#include "CircleComponent.h"
#include "AssetManager.h"
#include "Flipbook.h"
#include "World.h"
#include "Level.h"
#include "AlgorithmUtils.h"
#include "Tilemap.h"
#include "TilemapActor.h"

Enemy::Enemy() {

	SetEnemyAnimation();

	_square = std::make_shared<SquareComponent>();
	_square->SetSize({ 50.f, 50.f });

	_circle = std::make_shared<CircleComponent>();
	_circle->SetCollisionLayer(CLT_Trace);
	_circle->SetRadius(100.f);


	AddComponent(_square);
	AddComponent(_circle);

	SetMaxSpeed(60.f);
}

Enemy::~Enemy() {}

void Enemy::Init()
{
	Super::Init();

	_square->_beginOverlapDelegate.BindDelegate(this, &Enemy::BeginOverlapFunction);
	_circle->_endOverlapDelegate.BindDelegate(this, &Enemy::EndOverlapFunction);

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
		EnemyMove(DeltaTime);
		break;
	case ActionState::AS_Attack:
		break;
	}
	
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	//SetState(ActionState::AS_Attack);
	std::shared_ptr<Collider> collider = dynamic_pointer_cast<SquareComponent>(comp.lock());
	if (collider) {
		if (collider->GetOwner() == other.lock()) // ���� ������ ������Ʈ��� (���� flag �Ҵ��ص� �ɰͰ���)
			return;
		SetPos(GetPos() - collider->GetIntersect());
		SetSpeed(0.f);
	}
}


void Enemy::EndOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
	Chase();
}

float Enemy::TakeDamage(float damageAmount, std::weak_ptr<Actor> eventInstigator, std::weak_ptr<Actor> damageCauser)
{
	float damage = Super::TakeDamage(damageAmount, eventInstigator, damageCauser);

	GetDamage(damage);

	return damage;
}


void Enemy::UpdateAnimation()
{
	SetFlipbook(_move[_dir]);
}

void Enemy::SetEnemyAnimation()
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

void Enemy::EnemyMove(float DeltaTime)
{
	Vector2D dir = (GetDestPos() - GetPos());
	float dist = dir.Length();
	if (dir.Length() < 5.f) // ���������� ����� ������
	{
		SetPos(GetDestPos());
		SetSpeed(0.f);
		SetState(ActionState::AS_Idle);
	}
	// ���������� �ε巴�� �����̵��� ����
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
		float dist = std::abs(dir.X) + std::abs(dir.Y); // �밢���� �Ű澲�� �ʰ� �����¿츸 ���
		if (dist == 1.f) // �ٷ� ���̶��
		{
			SetDir(GetLookAtDir(target->GetPos()));
			SetState(ActionState::AS_Attack);
			SetWaitSeconds(GetMaxWaitSeconds());
		}
		else {
			// ��ǥ���� ���� ã�� 1ĭ �̵��ϰ� �ٽ� ã�� �� �ݺ�
			// (��귮�� �δ��� �ǳ� �� �ڿ�������. �δ�Ǹ� ���� �ð��� ã���� ����)
			std::vector<Vector2D> path;
			Vector2D targetCellPos = tmActor->ConvertToTilemapPos(target->GetPos());
			AlgorithmUtils::FindPathAStar(GetCellPos(), targetCellPos, OUT path);
			{
				// index 0�� ���� ��ġ
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

Dir Enemy::GetLookAtDir(Vector2D pos)
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

Vector2D Enemy::GetDirVector2D(Dir dir)
{
	// enum Dir�� ������ �����ش�. (�����¿�)
	static Vector2D nextDir[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // ���� ����
	return nextDir[dir];
}

void Enemy::GetDamage(float damage)
{
	damage -= _enemyStat.defence;
	if (damage <= 0)
		return;

	_enemyStat.hp = max(0.f, _enemyStat.hp - damage);
	if (_enemyStat.hp == 0.f)
	{
		std::shared_ptr<Level> level = World::GetCurrentLevel();
		if (level)
			level->RemoveActor(weak_from_this());
	}
}

void Enemy::SetCellPos(const Vector2D& cellPos)
{
	_cellPos = cellPos;

	std::shared_ptr<TilemapActor> tmActor = Level::GetCurrentTilemapActor();
	if (tmActor == nullptr)
		return;

	SetDestPos(tmActor->GetCellPos(cellPos));
}

void Enemy::SetDir(Dir dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	// ������ �ٲ�� Animation�� ���¿� �°� �ٲ��ش�.
	UpdateAnimation();
}

void Enemy::SetState(ActionState state)
{
	if (_state == state)
		return;

	_state = state;
	// ���°� �ٲ�� Animation�� ���¿� �°� �ٲ��ش�.
	UpdateAnimation();
}
