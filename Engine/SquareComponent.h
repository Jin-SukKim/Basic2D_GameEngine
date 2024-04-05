#pragma once
#include "Collider.h"

class SquareComponent : public Collider
{
	GENERATE_BODY(SquareComponent, Collider)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(std::weak_ptr<Collider> other);

public:
	void SetSize(Vector2D size) {
		_size = size;
	}
	Vector2D GetSize() const {
		return _size;
	}

	RECT GetRect();
private:
	Vector2D _size = Vector2D::Zero;
};

