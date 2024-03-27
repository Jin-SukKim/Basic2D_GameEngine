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
	// 키보드 상태 가져오기
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key) {
		// 키가 눌려있으면 true
		if (asciiKeys[key] & 0x80) {
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 PRESS
			if (state == KeyState::Down || state == KeyState::Pressed)
				state = KeyState::Pressed;
			else
				state = KeyState::Down; // 처음 눌리면
		}
		else {
			KeyState& state = _states[key];

			// 이전 프레임에 키를 누른 상태라면 Up
			if (state == KeyState::Pressed || state == KeyState::Down)
				state = KeyState::Up;
			else
				state = KeyState::None; // 안눌렸으면
		}
	}

	SetMousePos();
}

void InputManager::SetMousePos()
{
	// Mouse Pos
	::GetCursorPos(&_mousePos); // 커서의 좌표 (실제 모니터 화면에서의)
	::ScreenToClient(_hwnd, &_mousePos); // 화면 좌표에서 클라이언트 좌표로 변환

	if (::GetWindowRect(_hwnd, &_rect)) { // screen size 가져오기
		_mousePos.x = std::clamp(static_cast<int>(_mousePos.x), 0, static_cast<int>(_rect.right - _rect.left));
		_mousePos.y = std::clamp(static_cast<int>(_mousePos.y), 0, static_cast<int>(_rect.bottom - _rect.top));
	}
}
