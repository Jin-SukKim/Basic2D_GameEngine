#include "pch.h"
#include "InputManager.h"

InputManager::~InputManager()
{
}

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_states.resize(KEY_TYPE_COUNT, KeyState::None);
}

void InputManager::Tick()
{
	BYTE asciiKeys[KEY_TYPE_COUNT] = {}; // 256
	// Ű���� ���� ��������
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key) {
		// Ű�� ���������� true
		if (asciiKeys[key] & 0x80) {
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KeyState::Down || state == KeyState::Pressed)
				state = KeyState::Pressed;
			else
				state = KeyState::Down; // ó�� ������
		}
		else {
			KeyState& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� Up
			if (state == KeyState::Pressed || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None; // �ȴ�������
		}
	}

	SetMousePos();
}

void InputManager::SetMousePos()
{
	// Mouse Pos
	::GetCursorPos(&_mousePos); // Ŀ���� ��ǥ (���� ����� ȭ�鿡����)
	::ScreenToClient(_hwnd, &_mousePos); // ȭ�� ��ǥ���� Ŭ���̾�Ʈ ��ǥ�� ��ȯ

	if (::GetWindowRect(_hwnd, &_rect)) { // screen size ��������
		_mousePos.x = std::clamp(static_cast<int>(_mousePos.x), 0, static_cast<int>(_rect.right - _rect.left));
		_mousePos.y = std::clamp(static_cast<int>(_mousePos.y), 0, static_cast<int>(_rect.bottom - _rect.top));
	}
}
