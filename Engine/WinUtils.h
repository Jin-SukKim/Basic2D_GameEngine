#pragma once

class WinUtils
{
public:
	static void DrawText(HDC hdc, const Vector2D& pos, const std::wstring& str);
	static void DrawRect(HDC hdc, const Vector2D& pos, const int32& w, const int32& h);
	static void DrawCircle(HDC hdc, const Vector2D& pos, const int32& radius);
	static void DrawLine(HDC hdc, const Vector2D& from, const Vector2D& to);
};

