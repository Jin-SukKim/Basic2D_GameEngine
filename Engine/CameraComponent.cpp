#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "World.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Init()
{
}

void CameraComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Vector2D pos = GetPos();

	// TODO: World에 저장된 A
	// background map size에서 clamp (보정)
	pos.X = std::clamp(pos.X, 400.f, 3024.f - 400.f);
	pos.Y = std::clamp(pos.Y, 300.f, 2064.f - 300.f);

	World::SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}
