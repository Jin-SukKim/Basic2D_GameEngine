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
	uint64 _frequency = 0; // 성능 카운터의 빈도수
	uint64 _prevCount = 0; // 이전 CPU 클락 값 (CPU 클락값 == 성능 카운터의 값)
	float _deltaTime = 0.f; // (currentCount - _prevCount) / _frequency

	uint32 _frameCount = 0; // Frame 수
	float _frameTime = 0.f; // Frame 수가 될때 까지 경과된 총 시간 (ex: 6 frame동안 10ms 경과, 10ms = frameTime)
	uint32 _fps = 0;		// frameCount / frameTime = frame/sec
};
