#pragma once
#include "Component.h"

class Texture;

class TextureComponent : public Component {
	GENERATE_BODY(TextureComponent, Component)
public:
	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;


private:
	std::shared_ptr<Texture> _texture;
};

