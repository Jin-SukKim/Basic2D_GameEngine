#pragma once

// WinAPI에 정의되있는걸 좀더 쓰기 편하게
enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,

	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	SpaceBar = VK_SPACE,

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E'
};

enum class KeyState
{
	None,
	Pressed,
	Down,
	Up,

	End
};

#define KEY_TYPE_COUNT static_cast<int32>(UINT8_MAX)+1
#define KEY_STATE_COUNT static_cast<int32>(KeyState::End)