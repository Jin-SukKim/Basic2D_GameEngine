#include "pch.h"
#include "Enemy.h"
#include "SquareComponent.h"

Enemy::Enemy() {
	_square = std::make_shared<SquareComponent>();
	_square->SetSize({ 200.f, 200.f });
	AddComponent(_square);

}

Enemy::~Enemy() {}

void Enemy::Init()
{
	Super::Init();
}

void Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}
