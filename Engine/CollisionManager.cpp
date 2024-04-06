#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Tick()
{
	std::vector<std::shared_ptr<Collider>>& colliders = _colliders;

	for (int32 i = 0; i < colliders.size(); ++i) {
		std::shared_ptr<Collider> src = colliders[i];

		for (int32 j = i + 1; j < colliders.size(); ++j) {
			std::shared_ptr<Collider> dest = colliders[j];

			// 충돌했는지 확인
			if (src->CheckCollision(dest)) {
				if (src->IsCollided(dest) == false) {
					// TODO : OnComponentBeginOverlap 함수 부르기
					src->OnComponentBeginOverlap(src, dest);
					dest->OnComponentBeginOverlap(dest, src);

					src->AddCollisionSet(dest); // 서로 충돌했으니 서로 추가
					dest->AddCollisionSet(src);
				}
			}
			else {
				// 이전까지 충동했다 더이상 충돌하지 않는다면
				if (src->IsCollided(dest)) {
					// TODO : OnComponentEndOverlap 함수 부르기
					src->OnComponentEndOverlap(src, dest);
					dest->OnComponentEndOverlap(dest, src);

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
