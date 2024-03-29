#pragma once

class Texture
{
public:
	Texture();
	virtual ~Texture();

	bool LoadBmp(HWND hwnd, const std::wstring& path);

public:
	HDC GetDC();

	void SetSize(Vector2D size) { _size = size; }
	Vector2D GetSize() { return _size; }

	void SetTransparent(uint32 transparent) { _transparent = transparent;	}
	uint32 GetTransparent() { return _transparent; }

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	Vector2D _size = {};
	// 지금 사용하는 이미지의 bit 수준이 24bit이므로 RGB사용, 이미지에 따라 RGBA일수도 있다.
	// 이미지가 RGBA 비트를 사용하면 필요없지만 RGB사용하면 필요
	uint32 _transparent = RGB(255, 0, 255); // 거의 활용안하는 색으로 초기설정

};

