#include "pch.h"
#include "SquareComponent.h"

SquareComponent::SquareComponent() : Collider(ColliderType::CT_Square) {}

SquareComponent::~SquareComponent() {}

void SquareComponent::Init()
{
}

void SquareComponent::Tick(float DeltaTime)
{
}

void SquareComponent::Render(HDC hdc)
{
}

bool SquareComponent::CheckCollision(std::weak_ptr<Collider> other)
{
	return false;
}
