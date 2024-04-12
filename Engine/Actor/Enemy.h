#pragma once
#include "GameActor.h"

class CircleComponent;
class Collider;

class Enemy : public GameActor
{
	GENERATE_BODY(Enemy, GameActor)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	void EndAttackRange(std::weak_ptr<Collider> comp, std::weak_ptr<Actor> other, std::weak_ptr<Collider> otherComp);

protected:
	virtual void Set2DAnimation() override;
	virtual void UpdateAnimation() override;
	virtual void Move(float DeltaTime) override;
	virtual void Attack(float DeltaTime) override;

private:
	void Chase();

public:
	void SetWaitSeconds(float seconds) { _waitSeconds = seconds; }
	float GetWaitSeconds() const { return _waitSeconds; }

	void SetMaxWaitSeconds(float seconds) { _maxWaitSeconds = seconds; }
	float GetMaxWaitSeconds() const { return _maxWaitSeconds; }

private:
	std::shared_ptr<CircleComponent> _circle;

	float _waitSeconds = 0.f;
	float _maxWaitSeconds = 1.f;

	std::weak_ptr<Actor> _target;
};

