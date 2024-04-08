#include "pch.h"
#include "Enemy.h"
#include "SquareComponent.h"
#include "AssetManager.h"
#include "Flipbook.h"
#include "World.h"
#include "Level.h"

Enemy::Enemy() {

	SetEnemyAnimation();

	_square = std::make_shared<SquareComponent>();
	_square->SetSize({ 50.f, 50.f });
	AddComponent(_square);
}

Enemy::~Enemy() {}

void Enemy::Init()
{
	Super::Init();

	SetDir(DIR_Left);
}

void Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemyMove(DeltaTime);
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::BeginOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
}

void Enemy::EndOverlapFunction(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp)
{
}

void Enemy::OnDamaged(std::weak_ptr<Actor> attacker)
{
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
}

void Enemy::EnemyMove(float DeltaTime)
{
	SetPos(GetPos() + GetSpeed() * DeltaTime);
}

void Enemy::Chase()
{
	std::shared_ptr<Actor> target = _target.lock();
	if (target == nullptr)
		target = World::GetCurrentLevel()->FindClosestTarget(GetPos());


	if (target) {
		Vector2D dir = target->GetPos() - GetPos();
		float dist = std::abs(dir.X) + std::abs(dir.Y); // �밢���� �Ű澲�� �ʰ� �����¿츸 ���
		if (dist == 1) // �ٷ� ���̶��
		{
			SetDir(GetLookAtDir(target->GetPos()));
			SetState(ActionState::AS_Attack);
			SetWaitSeconds(GetMaxWaitSeconds());
		}
		else {
			// ��ǥ���� ���� ã�� 1ĭ �̵��ϰ� �ٽ� ã�� �� �ݺ�
			// (��귮�� �δ��� �ǳ� �� �ڿ�������. �δ�Ǹ� ���� �ð��� ã���� ����)
			std::vector<Vector2D> path;

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

void Enemy::FindPath(Vector2D pos, Vector2D targetPos, std::vector<Vector2D>& path)
{
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
