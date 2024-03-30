#pragma once
#include "Texture.h"

class Sprite : public Texture
{
public:
	Sprite(std::shared_ptr<Texture> texture, Vector2D& pos, Vector2D& size);
	virtual ~Sprite();

public:
	void SetTexture(std::shared_ptr<Texture> texture) { _texture = std::move(texture); }

	Vector2D GetSpritePos() { return _spritePos; }
	void SetSpritePos(Vector2D pos) { _spritePos = pos; }

	Vector2D GetSpriteSize() { return _spriteSize; }
	void SetSpriteSize(Vector2D size) { _spriteSize = size; }


private:
	std::shared_ptr<Texture> _texture;
	Vector2D _spritePos;
	Vector2D _spriteSize;
};

