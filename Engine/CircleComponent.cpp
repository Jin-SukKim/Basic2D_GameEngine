#include "pch.h"
#include "CircleComponent.h"

CircleComponent::CircleComponent() : Collider(ColliderType::CT_Circle) {}

CircleComponent::~CircleComponent() {}

void CircleComponent::Init()
{
}

void CircleComponent::Tick(float DeltaTime)
{
}

void CircleComponent::Render(HDC hdc)
{
}

bool CircleComponent::CheckCollision(std::weak_ptr<Collider> other)
{
	return false;
}
