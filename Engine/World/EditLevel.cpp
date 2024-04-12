#include "pch.h"
#include "EditLevel.h"
#include "Manager\InputManager.h"
#include "Manager\AssetManager.h"
#include "Engine.h"
#include "Utils\WinUtils.h"

EditLevel::EditLevel()
{
}

EditLevel::~EditLevel()
{
}

void EditLevel::Init()
{
	_resourcePath = GET_SINGLE(AssetManager)->GetResourcePath();
	_resourcePath = _resourcePath / L"EditLevel";
}

void EditLevel::Tick(float DeltaTime)
{
	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::LeftMouse))
		DrawLine();

	// �׸� �̾ �׸���
	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::RightMouse))
		StopDraw();

	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::C))
		Clear();

	if (GET_SINGLE(InputManager)->GetEventPressed(KeyType::LCtrl) && GET_SINGLE(InputManager)->GetEventDown(KeyType::Z))
		Undo();

	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::P))
		SaveDrawing(L"Draw.txt");

	if (GET_SINGLE(InputManager)->GetEventDown(KeyType::L))
		LoadDrawing(L"Draw.txt");
}

void EditLevel::Render(HDC hdc)
{
	for (auto& [from, to] : _lines) {
		Vector2D p1 = from;
		Vector2D p2 = to;

		WinUtils::DrawLine(hdc, p1, p2);
	}
}

void EditLevel::DrawLine()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	if (_setOrigin) { // ���� ��ġ
		_lastPos = mousePos;
		_setOrigin = false;
	}
	else { // ���� ��ġ
		_lines.push_back({ _lastPos, mousePos });
		_lastPos = mousePos;
	}
}

void EditLevel::StopDraw()
{
	_setOrigin = true;
}

bool EditLevel::SaveDrawing(const std::wstring& file)
{
	std::wofstream ofs;

	std::filesystem::path path = _resourcePath / file;
	ofs.open(path, std::ios::out); // ������ ������ �����
	if (!ofs.is_open())
		return false;

	// �׸��� Local Space�� ����(�߾�)�� �����ϱ� ���� �׸� object�� �߾����� ã��
	int32 minX = INT32_MAX;
	int32 minY = INT32_MAX;
	int32 maxX = INT32_MIN;
	int32 maxY = INT32_MIN;

	// ���� �׷��� ��ǥ�� min, max�� ã��
	for (auto& [from, to] : _lines) {
		minX = min(min(minX, from.x), to.x);
		minY = min(min(minY, from.y), to.y);
		maxX = max(max(maxX, from.x), to.x);
		maxY = max(max(maxY, from.y), to.y);
	}

	// minX + maxX�Ҷ� Ȥ�� int32 ������ ������
	int32 midX = minX + static_cast<int>((maxX - minX) * 0.5f); 
	int32 midY = minY + static_cast<int>((maxY - minY) * 0.5f);

	// Line�� ����
	ofs << static_cast<int32>(_lines.size()) << std::endl;

	for (auto& line : _lines) {
		POINT from = line.first;
		from.x -= midX;
		from.y -= midY;
		
		POINT to = line.second;
		to.x -= midX;
		to.y -= midY;

		std::wstring str = std::format(L"({0},{1})->({2},{3})", from.x, from.y, to.x, to.y);
		ofs << str << std::endl;
	}

	ofs.close();
	return true;
}

bool EditLevel::LoadDrawing(const std::wstring& file)
{
	std::wifstream ifs;

	std::filesystem::path path = _resourcePath / file;
	ifs.open(path);
	if (!ifs.is_open())
		return false;

	Clear();

	// ���� ����
	int32 count;
	ifs >> count;

	// ȭ���� ���߾�
	int32 midX = static_cast<int>(Engine::GetScreenWidth() * 0.5f);
	int32 midY = static_cast<int>(Engine::GetScreenHeight() * 0.5f);

	for (int32 i = 0; i < count; ++i) {
		POINT pt1;
		POINT pt2;

		std::wstring str;
		ifs >> str;
		::swscanf_s(str.c_str(), L"(%d,%d)->(%d,%d)", &pt1.x, &pt1.y, &pt2.x, &pt2.y);

		// ȭ�� �߾ӿ� �׷��ֱ�
		pt1.x += midX;
		pt1.y += midY;
		pt2.x += midX;
		pt2.y += midY;

		_lines.push_back({ pt1, pt2 });
	}
	
	StopDraw();

	ifs.close();
	return true;
}

void EditLevel::Undo()
{
	if (_lines.empty())
		return;

	_lines.pop_back();
	_lastPos = _lines.back().second;
}

void EditLevel::Clear()
{
	_lines.clear();
	StopDraw();
}

