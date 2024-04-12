#pragma once
#include "Texture.h"

struct FlipbookInfo {
	std::shared_ptr<Texture> texture = nullptr;
	std::wstring name = L"";
	Vector2D spriteSize = Vector2D::Zero;
	int32 start = 0;
	int32 end = 0;
	int32 line = 0; // texture의 몇번째 줄에 있는지
	float duration = 1.f;
	bool loop = true;
};

class Flipbook
{
public:
	Flipbook();
	Flipbook(const FlipbookInfo& info);
	~Flipbook();

public:
	virtual void SetInfo(const FlipbookInfo& info) { _info = info; }
	const FlipbookInfo& GetInfo() const { return _info; }

private:
	FlipbookInfo _info;
};

