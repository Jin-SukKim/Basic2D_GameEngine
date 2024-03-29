#pragma once
#include "Component.h"

class Texture;

class TextureComponent : public Component {
	using Super = Component;
public:
	TextureComponent(ObjectType type = ObjectType::Component);
	virtual ~TextureComponent();

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Render(HDC hdc);


private:
	std::shared_ptr<Texture> _texture;
};

