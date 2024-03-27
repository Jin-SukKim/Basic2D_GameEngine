#pragma once

// Singleton Pattenr
class InputManager
{
	GENERATE_SINGLE(InputManager) // UE�� Generate_body�� �̷������� ����������� ������?
public:
	~InputManager();

	void Init(HWND hwnd);
	void Tick();

	bool GetButtonDown(KeyType key) { return GetState(key) == KeyState::Down;	}
	bool GetButtonPressed(KeyType key) { return GetState(key) == KeyState::Pressed;	}
	bool GetButtonUp(KeyType key) { return GetState(key) == KeyState::Up;}

	void SetMousePos();
	POINT GetMousePos() { return _mousePos; }

private:
	KeyState GetState(KeyType key) { return _states[static_cast<uint8>(key)]; }
private:
	HWND _hwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos;
	RECT _rect;
};

