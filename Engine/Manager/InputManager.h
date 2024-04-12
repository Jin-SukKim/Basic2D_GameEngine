#pragma once

// Singleton Pattenr
class InputManager
{
	GENERATE_SINGLE(InputManager) // UE�� Generate_body�� �̷������� ����������� ������?
public:
	~InputManager();

	void Init(HWND hwnd);
	void Tick();

	bool GetEventDown(KeyType key) const { return GetState(key) == KeyState::Down;	}
	bool GetEventPressed(KeyType key)const { return GetState(key) == KeyState::Pressed;	}
	bool GetEventUp(KeyType key) const { return GetState(key) == KeyState::Up;}

	void SetMousePos();
	POINT GetMousePos() const { return _mousePos; }
	
	// TODO : Button Event�� FunctionPtr ����
	// parameter : KeyType, EventType, owner, function_ptr

private:
	KeyState GetState(KeyType key) const { return _states[static_cast<uint8>(key)]; }
private:
	HWND _hwnd = 0;
	std::vector<KeyState> _states;
	POINT _mousePos;
	RECT _rect;

	// TODO: ���� TriggerEvent Type�� ����� ����ϴ� �͵�?
};
