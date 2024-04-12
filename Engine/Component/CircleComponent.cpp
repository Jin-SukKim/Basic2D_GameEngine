#include "pch.h"
#include "CircleComponent.h"
#include "Actor\Actor.h"
#include "World\World.h"
#include "Engine.h"
#include "Utils\WinUtils.h"
#include "SquareComponent.h"

CircleComponent::CircleComponent() : Collider(ColliderType::CT_Circle) {}

CircleComponent::~CircleComponent() {}

void CircleComponent::Init()
{
	Super::Init();
}

void CircleComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void CircleComponent::Render(HDC hdc)
{
	Super::Render(hdc);

	const Vector2D camPos = World::GetCameraPos();
	Vector2D pos = GetPos();
	pos -= camPos - Engine::GetScreenSize() * 0.5f;

	HPEN myPen = (HPEN)::GetStockObject(DC_PEN);
	HPEN oldPen = (HPEN)::SelectObject(hdc, myPen);

	HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);

	::SetDCPenColor(hdc, RGB(255, 0, 0));

	WinUtils::DrawCircle(hdc, pos, static_cast<int32>(_radius));

	::SelectObject(hdc, oldBrush);
	::DeleteObject(myBrush);

	::SelectObject(hdc, oldPen);
	::DeleteObject(myPen);
}


bool CircleComponent::CheckCollision(std::weak_ptr<Collider> other)
{
	if (Super::CheckCollision(other) == false) // 서로 충돌할 수 있는지 확인
		return false;

	std::shared_ptr<Collider> collider = other.lock();
	if (collider == nullptr)
		return false;

	switch (collider->GetColliderType())
	{
	case ColliderType::CT_Square:
		return CheckCollisionCircleToSquare(std::dynamic_pointer_cast<CircleComponent>(shared_from_this()), std::dynamic_pointer_cast<SquareComponent>(collider));
	case ColliderType::CT_Circle:													   
		return CheckCollisionCircleToCircle(std::dynamic_pointer_cast<CircleComponent>(shared_from_this()), std::dynamic_pointer_cast<CircleComponent>(collider));
	default:
		break;
	}
	return false;
}
