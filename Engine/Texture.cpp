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
	HDC hdc = ::GetDC(hwnd); // DC 생성

	_hdc = ::CreateCompatibleDC(hdc);

	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	if (_bitmap == NULL) {
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
		return false;
	}

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap); // 새로 생성된 dc로 교체
	::DeleteObject(prev); // 기존 dc 삭제

	BITMAP bitMap = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bitMap); // 로드한 이미지의 정보 가져오기
	_size.X = bitMap.bmWidth;
	_size.Y = bitMap.bmHeight;
	
	return true;
}
