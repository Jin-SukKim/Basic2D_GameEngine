#pragma once

class Timer
{
public:
	Timer(float wait);
	~Timer() {}

	bool TimerTick(float deltaTime);

public:
	// 함수 포인터 + 함수 객체 모두 받을 수 있다. (return type = void, parameter = void)
	std::function<void(void)> _execute = nullptr;
private:
	float _wait;
	float _sumTime = 0.f;
};

