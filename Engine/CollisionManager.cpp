#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Tick(float DeltaTime)
{
}

void CollisionManager::Render()
{
	std::vector<std::shared_ptr<Collider>>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); ++i) {
		std::shared_ptr<Collider> src = colliders[i];
		
		for (int32 j = i + 1; j < colliders.size(); ++j) {
			std::shared_ptr<Collider> dest = colliders[j];

			// �浹�ߴ��� Ȯ��
			if (src->CheckCollision(dest)) {
				if (src->IsCollided(dest) == false) {
					// TODO : OnComponentBeginOverlap �Լ� �θ���
					src->AddCollisionSet(dest); // ���� �浹������ ���� �߰�
					dest->AddCollisionSet(src);
				}
			}
			else {
				// �������� �浿�ߴ� ���̻� �浹���� �ʴ´ٸ�
				if (src->IsCollided(dest)) {
					// TODO : OnComponentEndOverlap �Լ� �θ���
					src->RemoveCollisionSet(dest);
					dest->RemoveCollisionSet(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(std::shared_ptr<Collider> collider)
{
	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(std::shared_ptr<Collider> collider)
{
	auto it = std::remove(_colliders.begin(), _colliders.end(), collider);
	_colliders.erase(it, _colliders.end());
}
