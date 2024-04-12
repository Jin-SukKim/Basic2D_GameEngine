#pragma once

// Singleton Pattenr
class InputManager
{
	GENERATE_SINGLE(InputManager) // UE의 Generate_body가 이런식으로 만들어져있지 않을까?
public:
	~InputManager();

	void Init(HWND hwnd);
	void Tick();

	bool GetEventDown(KeyType key) const { return GetState(key) == KeyState::Down;	}
	bool GetEventPressed(KeyType key)const { return GetState(key) == KeyState::Pressed;	}
	bool GetEventUp(KeyType key) const { return GetState(key) == KeyState::Up;}

	void SetMousePos();
	POINT GetMousePos() const { return _mousePos; }
	
	// TODO : Button Event에 FunctionPtr 연결
	// parameter : KeyType, EventType, owner, function_ptr

private:
	KeyState GetState(KeyType key) const { return _states[static_cast<uint8>(key)]; }
private:
	HWND _hwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos;
	RECT _rect;

	// TODO: 따로 TriggerEvent Type을 만들어 사용하는 것도?
};
