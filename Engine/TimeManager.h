#pragma once

class TimeManager
{
public:
	TimeManager() {}
	~TimeManager() {}

	void Init();
	void Tick();

	uint32 GetFPS() {
		return _fps;
	}
	float GetDeltaTime() {
		return _deltaTime;
	}

private:
	uint64 _frequency = 0; // ���� ī������ �󵵼�
	uint64 _prevCount = 0; // ���� CPU Ŭ�� �� (CPU Ŭ���� == ���� ī������ ��)
	float _deltaTime = 0.f; // (currentCount - _prevCount) / _frequency

	uint32 _frameCount = 0; // Frame ��
	float _frameTime = 0.f; // Frame ���� �ɶ� ���� ����� �� �ð� (ex: 6 frame���� 10ms ���, 10ms = frameTime)
	uint32 _fps = 0;		// frameCount / frameTime = frame/sec
};
