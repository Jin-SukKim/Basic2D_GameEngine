#pragma once

class Timer
{
public:
	Timer(float wait);
	~Timer() {}

	bool TimerTick(float deltaTime);

public:
	// �Լ� ������ + �Լ� ��ü ��� ���� �� �ִ�. (return type = void, parameter = void)
	std::function<void(void)> _execute = nullptr;
private:
	float _wait;
	float _sumTime = 0.f;
};

