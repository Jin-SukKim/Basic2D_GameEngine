#include "pch.h"
#include "WinUtils.h"

void WinUtils::DrawText(HDC hdc, Vector2D pos, const std::wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.X), static_cast<int32>(pos.Y), str.c_str(), static_cast<int32>(str.size()));
}

void WinUtils::DrawRect(HDC hdc, Vector2D pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.X - w / 2), static_cast<int32>(pos.Y - h / 2), static_cast<int32>(pos.X + w / 2), static_cast<int32>(pos.Y + h / 2));
}

void WinUtils::DrawCircle(HDC hdc, Vector2D pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.X - radius), static_cast<int32>(pos.Y - radius), static_cast<int32>(pos.X + radius), static_cast<int32>(pos.Y + radius));
}

void WinUtils::DrawLine(HDC hdc, Vector2D from, Vector2D to)
{
	::MoveToEx(hdc, static_cast<int32>(from.X), static_cast<int32>(from.Y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.X), static_cast<int32>(to.Y));
}