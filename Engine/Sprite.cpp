#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> texture, Vector2D& pos, Vector2D& size) :
	_texture(std::move(texture)), _spritePos(pos), _spriteSize(size)
{
}

Sprite::~Sprite()
{
}
