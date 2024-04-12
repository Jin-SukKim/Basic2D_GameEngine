#pragma once

class Texture;

class Sprite
{
public:
	Sprite(std::shared_ptr<Texture> texture, Vector2D& spritePos, Vector2D& spriteSize);
	virtual ~Sprite();

public:
	void SetTexture(std::shared_ptr<Texture> texture) { _texture = std::move(texture); }

	HDC GetDC();
	int32 GetTransparent();
	
	Vector2D GetSpritePos() const { return _spritePos; }
	void SetSpritePos(Vector2D pos) { _spritePos = pos; }

	Vector2D GetSpriteSize() const { return _spriteSize; }
	void SetSpriteSize(Vector2D size) { _spriteSize = size; }

private:
	std::shared_ptr<Texture> _texture;
	Vector2D _spritePos;
	Vector2D _spriteSize;
};

