#pragma once
#include "Actor.h"

class Texture;

class TextureActor : public Actor
{
	using Super = Actor;
public:
	TextureActor();
	virtual ~TextureActor() override;

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

protected:
	std::shared_ptr<Texture> _texture;
};

