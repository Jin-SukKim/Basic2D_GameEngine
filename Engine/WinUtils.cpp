#include "pch.h"
#include "WinUtils.h"

void WinUtils::DrawText(HDC hdc, const Vector2D& pos, const std::wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.X), static_cast<int32>(pos.Y), str.c_str(), static_cast<int32>(str.size()));
}

void WinUtils::DrawRect(HDC hdc, const Vector2D& pos, const int32& w, const int32& h)
{
	::Rectangle(hdc, static_cast<int32>(pos.X - w / 2), static_cast<int32>(pos.Y - h / 2), static_cast<int32>(pos.X + w / 2), static_cast<int32>(pos.Y + h / 2));
}

void WinUtils::DrawCircle(HDC hdc, const Vector2D& pos, const int32& radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.X - radius), static_cast<int32>(pos.Y - radius), static_cast<int32>(pos.X + radius), static_cast<int32>(pos.Y + radius));
}

void WinUtils::DrawLine(HDC hdc, const Vector2D& from, const Vector2D& to)
{
	::MoveToEx(hdc, static_cast<int32>(from.X), static_cast<int32>(from.Y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.X), static_cast<int32>(to.Y));
}