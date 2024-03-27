#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// ms
	// ::GetTickCount64(); // 정밀도가 조금 떨어진다.

	// 더 정밀한 방법으로 시간 측정
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency)); // CPU 클락 빈도수
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU 클락
}

void TimeManager::Tick()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount)); // CPU 클락

	// (현재 Clock - 이전 Clock) / freq = deltaTime, ms로 표현하려면 1000을 곱해주면 된다.
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;			  // Frame 수
	_frameTime += _deltaTime; // Frame 개수만큼 경과한 시간 + 매 Frame마다 경과된 시간

	// FrameTime이 1초 경과
	if (_frameTime >= 1.f) {
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		// 초기화
		_frameCount = 0;
		_frameTime = 0.f;
	}
}
