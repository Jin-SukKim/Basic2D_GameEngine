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
	// ���� ����ϴ� �̹����� bit ������ 24bit�̹Ƿ� RGB���, �̹����� ���� RGBA�ϼ��� �ִ�.
	// �̹����� RGBA ��Ʈ�� ����ϸ� �ʿ������ RGB����ϸ� �ʿ�
	uint32 _transparent = RGB(255, 0, 255); // ���� Ȱ����ϴ� ������ �ʱ⼳��

};

