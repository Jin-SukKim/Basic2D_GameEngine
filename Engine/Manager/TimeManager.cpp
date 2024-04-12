#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	// ms
	// ::GetTickCount64(); // ���е��� ���� ��������.

	// �� ������ ������� �ð� ����
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency)); // CPU Ŭ�� �󵵼�
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU Ŭ��
}

void TimeManager::Tick()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount)); // CPU Ŭ��

	// (���� Clock - ���� Clock) / freq = deltaTime, ms�� ǥ���Ϸ��� 1000�� �����ָ� �ȴ�.
	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;			  // Frame ��
	_frameTime += _deltaTime; // Frame ������ŭ ����� �ð� + �� Frame���� ����� �ð�

	// FrameTime�� 1�� ���
	if (_frameTime >= 1.f) {
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		// �ʱ�ȭ
		_frameCount = 0;
		_frameTime = 0.f;
	}
}
