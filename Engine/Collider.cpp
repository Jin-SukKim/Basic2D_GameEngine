#include "pch.h"
#include "Collider.h"
#include "Actor.h"
#include "SquareComponent.h"
#include "CircleComponent.h"
#include "CollisionManager.h"

Collider::Collider() : _colliderType(ColliderType::CT_Square) {}

Collider::Collider(ColliderType colliderType) : _colliderType(colliderType) {}

Collider::~Collider() {
}


void Collider::Init()
{
	GET_SINGLE(CollisionManager)->AddCollider(shared_from_this());
}

void Collider::Tick(float DeltaTime)
{
}

void Collider::Render(HDC hdc)
{
	if (_showDebug == false)
		return;
}

void Collider::Clear()
{
	GET_SINGLE(CollisionManager)->RemoveCollider(shared_from_this());
}

bool Collider::CheckCollision(std::weak_ptr<Collider> other)
{
	std::shared_ptr<Collider> collider = other.lock();
	if (collider == nullptr)
		return false;

	uint8 layer = collider->GetCollisionLayer();
	if (_collisionFlag & (1 << layer))
		return true;

	return false;
}

void Collider::OnComponentBeginOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other)
{
	_beginOverlapDelegate(collider, other->GetOwner(), other);
}

void Collider::OnComponentEndOverlap(std::shared_ptr<Collider> collider, std::shared_ptr<Collider> other)
{
	_endOverlapDelegate(collider, other->GetOwner(), other);
}

// https://blog.naver.com/winterwolfs/10165506488
bool Collider::CheckCollisionSquareToSqaure(std::weak_ptr<SquareComponent> b1, std::weak_ptr<SquareComponent> b2)
{
	std::shared_ptr<SquareComponent> square1 = b1.lock();
	if (square1 == nullptr)
		return false;
	std::shared_ptr<SquareComponent> square2 = b2.lock();
	if (square2 == nullptr)
		return false;

	RECT r1 = square1->GetRect();
	RECT r2 = square2->GetRect();

	RECT intersect = {};

	// 겹치는 영역까지 알려준다.
	bool check = ::IntersectRect(&intersect, &r1, &r2);
	
	{
		// 최대한 간단한 버전 (정확하지가 않다)
		// Frame이 낮으면 제대로 동작하지 않는다. 이유가 뭘까?
		Vector2D intersectVec = Vector2D::Zero;
		
		// 정확히 겹친 영역만큼만 계산한다면 border가 겹칠수 있다. (미세한만큼 추가로 보정해 계산해준다)
		int32 w = intersect.right - intersect.left + 1;
		int32 h = intersect.bottom - intersect.top + 1;

		if (w > h) {
			// 위에서 충돌했으면
			if (intersect.top == r2.top) {
				intersectVec.Y += h;
			}
			else {
				intersectVec.Y -= h;
			}
		}
		else {
			// 왼쪽에서 충돌했으면
			if (intersect.left == r2.left) {
				intersectVec.X += w;
			}
			else {
				intersectVec.X -= w;
			}
		}

		SetIntersect(intersectVec);
	}

	return check;

	// 두 사각형이 겹치는지만 알 수 있따.
	/*
	{
		const Vector2D pos1 = square1->GetOwner()->GetPos();
		const Vector2D halfSize1 = square1->GetSize() * 0.5f;

		const Vector2D pos2 = square2->GetOwner()->GetPos();
		const Vector2D halfSize2 = square2->GetSize() * 0.5f;
	
		// 두 사각형의 가장 작은 점과 큰 점을 찾아 비교
		const Vector2D min1 = pos1 - halfSize1;
		const Vector2D max1 = pos1 + halfSize1;

		const Vector2D min2 = pos2 - halfSize2;
		const Vector2D max2 = pos2 + halfSize2;

		// 두 사각형의 좌우 변들 중 겹치는 부분이 없다면
		// 두 사각형의 상하 변들 중 겹치는 부분이 없다면
		if (max1.X < min2.X || max2.X < min1.X ||  max1.Y < min2.Y || max2.Y < min1.Y)
			return false;
	}

	return true;
	*/
}

// https://dolphin.ivyro.net/file/mathematics/tutorial07.html
bool Collider::CheckCollisionCircleToSquare(std::weak_ptr<CircleComponent> c1, std::weak_ptr<SquareComponent> b1)
{
	std::shared_ptr<CircleComponent> c = c1.lock();
	if (c)
		return false;
	std::shared_ptr<SquareComponent> s = b1.lock();
	if (s)
		return false;

	// 사각형 정보
	const RECT org = s->GetRect();
	const Vector2D squarePos = s->GetPos();
	const Vector2D squareHalfSize = s->GetSize();

	// 원 정보
	const Vector2D circlePos = c->GetPos();
	const float radius = c->GetRadius();

	const int8 nZone = GetSquareZone(org, circlePos); // 원이 어느 방향에 있는지
	const Vector2D dist = circlePos - squarePos; // 원과 사각형의 거리

	switch (nZone)
	{
	// 사각형 바깥의 위, 아래 영역에서 원의 반지름과 작거나 같은지 확인해 충돌확인
	case 1:
	case 7:
	{
		float distY = std::fabs(dist.Y);
		if (distY <= (radius + squareHalfSize.Y))
			return true;
	}
	break;
	// 사각형의 왼쪽, 오른쪽 영역
	case 3:
	case 5:
	{
		float distX = std::fabs(dist.X);
		if (distX <= (radius + squareHalfSize.X))
			return true;
	}
	break;
	// 사각형 안
	case 4:
		return true;
	// 모서리 영역, 사각형의 각 모서리가 원의 내부에 포함되야 충돌한다.
	default:
	{
		// 왼쪽인지 오른쪽인지
		float cornerX = (nZone == 0 || nZone == 6) ?
			squarePos.X - squareHalfSize.X : squarePos.X + squareHalfSize.X;
		// 위쪽인지 아래쪽인지
		float cornerY = (nZone == 0 || nZone == 2) ?
			squarePos.Y - squareHalfSize.Y : squarePos.Y + squareHalfSize.Y;

		if (CheckPointInCircle(circlePos, radius, { cornerX, cornerY }))
			return true;
	}
	break;
	}

	return false;
}

bool Collider::CheckCollisionCircleToCircle(std::weak_ptr<CircleComponent> c1, std::weak_ptr<CircleComponent> c2)
{
	std::shared_ptr<CircleComponent> circle1 = c1.lock();
	if (circle1)
		return false;
	std::shared_ptr<CircleComponent> circle2 = c2.lock();
	if (circle2)
		return false;

	const Vector2D pos1 = circle1->GetOwner()->GetPos();
	const float radius1 = circle1->GetRadius();

	const Vector2D pos2 = circle2->GetOwner()->GetPos();
	const float radius2 = circle2->GetRadius();

	Vector2D dir = pos1 - pos2;
	const float dist = dir.Length();

	// 두 원의 각각의 중점끼리의 거리가 두 원의 반지름의 합보다 크면 false, 작거나 같으면 true
	return dist <= radius1 + radius2;
}

/*
	0 1 2
	3 4 5
	6 7 8

	4가 사각형의 위치, 그 외는 사각형의 바깥
*/
int8 Collider::GetSquareZone(const RECT& rect, const Vector2D& circlePos)
{
	int xZone = (circlePos.X < rect.left) ? 0 :
		(circlePos.X > rect.right) ? 2 : 1;

	int yZone = (circlePos.Y < rect.top) ? 0 :
		(circlePos.Y > rect.bottom) ? 2 : 1;

	return xZone + 3 * yZone;
}

bool Collider::CheckPointInCircle(const Vector2D& cPos, const Vector2D& radius, const Vector2D& point)
{
	Vector2D lengthSq = point - cPos;
	lengthSq = lengthSq.LengthSquared(); // 원의 중심과 점 사이의 거리

	// 반지름보다 멀다면
	if (lengthSq > (radius * radius))
		return false;

	return true;
}

// Bit 연산
/*
	// bit 연산 : >>, <<, &, |, ^, ~
	// 특정 비트 켜기
	flag = flag | (1 << CLT_WALL);

	// 특정 비트 끄기
	flag = flag & ~(1 << CLT_WALL);

	// 비트 체크
	bool ret = flag & (1 << CLT_WALL); // & 연산 후 모두 0인지 아닌지

	// 전체 켜기
	flag = ~0;
*/
void Collider::AddCollisionFlagLayer(CollisionLayerType layer)
{
	_collisionFlag |= (1 << layer); // 비트 켜기
}

void Collider::RemoveCollisionFlagLayer(CollisionLayerType layer)
{
	_collisionFlag &= ~(1 << layer); // 비트 끄기
}
