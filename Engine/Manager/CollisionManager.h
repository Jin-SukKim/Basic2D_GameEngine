#pragma once

class Collider;

class CollisionManager
{
	GENERATE_SINGLE(CollisionManager);
public:
	~CollisionManager();

	void Init();
	void Tick();

	void AddCollider(std::shared_ptr<Collider> collider);
	void RemoveCollider(std::shared_ptr<Collider> collider);

private:
	std::vector<std::shared_ptr<Collider>> _colliders;
};

