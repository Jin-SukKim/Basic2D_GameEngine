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

	// ��ġ�� �������� �˷��ش�.
	bool check = ::IntersectRect(&intersect, &r1, &r2);
	
	{
		// �ִ��� ������ ���� (��Ȯ������ �ʴ�)
		// Frame�� ������ ����� �������� �ʴ´�. ������ ����?
		Vector2D intersectVec = Vector2D::Zero;
		
		// ��Ȯ�� ��ģ ������ŭ�� ����Ѵٸ� border�� ��ĥ�� �ִ�. (�̼��Ѹ�ŭ �߰��� ������ ������ش�)
		int32 w = intersect.right - intersect.left + 1;
		int32 h = intersect.bottom - intersect.top + 1;

		if (w > h) {
			// ������ �浹������
			if (intersect.top == r2.top) {
				intersectVec.Y += h;
			}
			else {
				intersectVec.Y -= h;
			}
		}
		else {
			// ���ʿ��� �浹������
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

	// �� �簢���� ��ġ������ �� �� �ֵ�.
	/*
	{
		const Vector2D pos1 = square1->GetOwner()->GetPos();
		const Vector2D halfSize1 = square1->GetSize() * 0.5f;

		const Vector2D pos2 = square2->GetOwner()->GetPos();
		const Vector2D halfSize2 = square2->GetSize() * 0.5f;
	
		// �� �簢���� ���� ���� ���� ū ���� ã�� ��
		const Vector2D min1 = pos1 - halfSize1;
		const Vector2D max1 = pos1 + halfSize1;

		const Vector2D min2 = pos2 - halfSize2;
		const Vector2D max2 = pos2 + halfSize2;

		// �� �簢���� �¿� ���� �� ��ġ�� �κ��� ���ٸ�
		// �� �簢���� ���� ���� �� ��ġ�� �κ��� ���ٸ�
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

	// �簢�� ����
	const RECT org = s->GetRect();
	const Vector2D squarePos = s->GetPos();
	const Vector2D squareHalfSize = s->GetSize();

	// �� ����
	const Vector2D circlePos = c->GetPos();
	const float radius = c->GetRadius();

	const int8 nZone = GetSquareZone(org, circlePos); // ���� ��� ���⿡ �ִ���
	const Vector2D dist = circlePos - squarePos; // ���� �簢���� �Ÿ�

	switch (nZone)
	{
	// �簢�� �ٱ��� ��, �Ʒ� �������� ���� �������� �۰ų� ������ Ȯ���� �浹Ȯ��
	case 1:
	case 7:
	{
		float distY = std::fabs(dist.Y);
		if (distY <= (radius + squareHalfSize.Y))
			return true;
	}
	break;
	// �簢���� ����, ������ ����
	case 3:
	case 5:
	{
		float distX = std::fabs(dist.X);
		if (distX <= (radius + squareHalfSize.X))
			return true;
	}
	break;
	// �簢�� ��
	case 4:
		return true;
	// �𼭸� ����, �簢���� �� �𼭸��� ���� ���ο� ���ԵǾ� �浹�Ѵ�.
	default:
	{
		// �������� ����������
		float cornerX = (nZone == 0 || nZone == 6) ?
			squarePos.X - squareHalfSize.X : squarePos.X + squareHalfSize.X;
		// �������� �Ʒ�������
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

	// �� ���� ������ ���������� �Ÿ��� �� ���� �������� �պ��� ũ�� false, �۰ų� ������ true
	return dist <= radius1 + radius2;
}

/*
	0 1 2
	3 4 5
	6 7 8

	4�� �簢���� ��ġ, �� �ܴ� �簢���� �ٱ�
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
	lengthSq = lengthSq.LengthSquared(); // ���� �߽ɰ� �� ������ �Ÿ�

	// ���������� �ִٸ�
	if (lengthSq > (radius * radius))
		return false;

	return true;
}

// Bit ����
/*
	// bit ���� : >>, <<, &, |, ^, ~
	// Ư�� ��Ʈ �ѱ�
	flag = flag | (1 << CLT_WALL);

	// Ư�� ��Ʈ ����
	flag = flag & ~(1 << CLT_WALL);

	// ��Ʈ üũ
	bool ret = flag & (1 << CLT_WALL); // & ���� �� ��� 0���� �ƴ���

	// ��ü �ѱ�
	flag = ~0;
*/
void Collider::AddCollisionFlagLayer(CollisionLayerType layer)
{
	_collisionFlag |= (1 << layer); // ��Ʈ �ѱ�
}

void Collider::RemoveCollisionFlagLayer(CollisionLayerType layer)
{
	_collisionFlag &= ~(1 << layer); // ��Ʈ ����
}
