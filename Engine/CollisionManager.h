#pragma once

class Collider;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();
	void Tick(float DeltaTime);
	void Render();

	void AddCollider(std::shared_ptr<Collider> collider);
	void RemoveCollider(std::shared_ptr<Collider> collider);

private:
	std::vector<std::shared_ptr<Collider>> _colliders;
};

