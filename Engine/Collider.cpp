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
		
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;

		// ��Ȯ�� ��ģ ������ŭ�� ����Ѵٸ� border�� ��ĥ�� �ִ�. (�̼��Ѹ�ŭ �߰��� ������ ������ش�)
		if (w > h) {
			// ������ �浹������
			if (intersect.top == r2.top) {
				intersectVec.Y += h + 1;
			}
			else {
				intersectVec.Y -= h - 1;
			}
		}
		else {
			// ���ʿ��� �浹������
			if (intersect.left == r2.left) {
				intersectVec.X += w + 1;
			}
			else {
				intersectVec.X -= w - 1;
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

bool Collider::CheckCollisionCircleToSquare(std::weak_ptr<CircleComponent> c1, std::weak_ptr<SquareComponent> b1)
{
	std::shared_ptr<CircleComponent> c = c1.lock();
	if (c)
		return false;
	std::shared_ptr<SquareComponent> s = b1.lock();
	if (s)
		return false;

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