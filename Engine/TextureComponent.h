#pragma once
#include "Component.h"

class Texture;

class TextureComponent : public Component {
	GENERATE_BODY(TextureComponent, Component)
public:

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc);


private:
	std::shared_ptr<Texture> _texture;
};

