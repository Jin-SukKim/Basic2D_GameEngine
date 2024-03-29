#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::LoadBmp(HWND hwnd, const std::wstring& path)
{
	HDC hdc = ::GetDC(hwnd); // �� Texture�� �׸� DC ����

	_hdc = ::CreateCompatibleDC(hdc);

	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if (_bitmap == NULL) {
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
		return false;
	}

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap); // ���� ������ dc�� ��ü
	::DeleteObject(prev); // ���� dc ����

	BITMAP bitMap = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bitMap); // �ε��� �̹����� ���� ��������
	_size.X = static_cast<float>(bitMap.bmWidth);
	_size.Y = static_cast<float>(bitMap.bmHeight);
	
	return true;
}

HDC Texture::GetDC()
{
	return _hdc;
}
