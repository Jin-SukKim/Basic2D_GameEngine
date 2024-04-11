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
	Super::Tick(DeltaTime);
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
	if (_enable == false)
		return false;

	std::shared_ptr<Collider> collider = other.lock();
	if (collider == nullptr)
		return false;

	uint8 layer = collider->GetCollisionLayer();
	uint8 flag = collider->GetCollisionFlag();

	// �ϳ��� �浹 (Overlap)
	if (GetCollisionFlag() & layer)
		return true;

	// ���� �浹 �����ؾ� �浹 (��, ������ Hit), UEó�� HitEvent�� ���� �����?
	//if ((GetCollisionFlag() & layer) && (GetCollisionLayer() & flag))
	//	return true;

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
		const Vector2D pos1 = square1->GetPos();
		const Vector2D halfSize1 = square1->GetSize() * 0.5f;

		const Vector2D pos2 = square2->GetPos();
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
	if (c == nullptr)
		return false;
	std::shared_ptr<SquareComponent> s = b1.lock();
	if (s == nullptr)
		return false;

	// �簢�� ����
	const RECT org = s->GetRect();

	// �� ����
	const Vector2D circlePos = c->GetPos();
	const float radius = c->GetRadius();

	bool horizon = org.left <= circlePos.X && circlePos.X <= org.right;
	bool verticle = org.top <= circlePos.Y && circlePos.Y <= org.bottom;
	if (horizon || verticle) {
		// ���� ��������ŭ Ȯ���� �� ���ϱ�
		RECT exRect = {
			org.left - static_cast<LONG>(radius),
			org.top - static_cast<LONG>(radius),
			org.right + static_cast<LONG>(radius),
			org.bottom + static_cast<LONG>(radius),
		};

		// Ȯ���� �簢�� �ȿ� ���� �߽��� �ִ��� Ȯ��
		if (exRect.left < circlePos.X && circlePos.X < exRect.right
			&& exRect.top < circlePos.Y && circlePos.Y < exRect.bottom)
			return true;
	}
	else {
		Vector2D point = { static_cast<float>(org.left), static_cast<float>(org.top) };
		// �簢�� �»�� �������� ���ȿ� �ִ���
		if (CheckPointInCircle(circlePos, radius, point))
			return true;
		// �簢�� ���ϴ� �������� ���ȿ� �ִ���
		point.Y = static_cast<float>(org.bottom);
		if (CheckPointInCircle(circlePos, radius, point))
			return true;
		// �簢�� ���ϴ� �������� ���ȿ� �ִ���
		point.X = static_cast<float>(org.right);
		if (CheckPointInCircle(circlePos, radius, point))
			return true;
		// �簢�� ���� �������� ���ȿ� �ִ���
		point.Y = static_cast<float>(org.top);
		if (CheckPointInCircle(circlePos, radius, point))
			return true;
	}

	return false;
}

bool Collider::CheckCollisionCircleToCircle(std::weak_ptr<CircleComponent> c1, std::weak_ptr<CircleComponent> c2)
{
	std::shared_ptr<CircleComponent> circle1 = c1.lock();
	if (circle1 == nullptr)
		return false;
	std::shared_ptr<CircleComponent> circle2 = c2.lock();
	if (circle2 == nullptr)
		return false;

	const Vector2D pos1 = circle1->GetPos();
	const float radius1 = circle1->GetRadius();

	const Vector2D pos2 = circle2->GetPos();
	const float radius2 = circle2->GetRadius();

	Vector2D dir = pos1 - pos2;
	const float dist = dir.Length();

	// �� ���� ������ ���������� �Ÿ��� �� ���� �������� �պ��� ũ�� false, �۰ų� ������ true
	return dist <= radius1 + radius2;
}

bool Collider::CheckPointInCircle(const Vector2D& cPos, const Vector2D& radius, const Vector2D& point)
{
	Vector2D lengthSq = (cPos - point).LengthSquared(); // ���� �߽ɰ� �� ������ �Ÿ�

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
