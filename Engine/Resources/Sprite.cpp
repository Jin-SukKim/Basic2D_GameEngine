#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(std::shared_ptr<Texture> texture, Vector2D& pos, Vector2D& size) :
	_texture(texture), _spritePos(pos), _spriteSize(size)
{
}

Sprite::~Sprite()
{
}

HDC Sprite::GetDC()
{
	return _texture->GetDC();
}

int32 Sprite::GetTransparent()
{
	return _texture->GetTransparent();
}
