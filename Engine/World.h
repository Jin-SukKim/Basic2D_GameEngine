#pragma once
#include "TimeManager.h"
#include "Timer.h"

class World
{
public:
	World();
	~World();

	void Init();
	void Tick();
	void Render(HDC hdc);
	
	TimeManager& GetWorldTimer() const {
		return *_timeManager;
	}

	// function_ptr�� function�� �޾� �����ð� �ڿ� ������ �� �ֵ���
	template<typename T>
	void SetTimer(T* owner, void(T::* func)(), float wait); // T type�� void() �Լ� �����͸� �޴´�.
private:
	std::unique_ptr<TimeManager> _timeManager;
};

// TODO: Thread�� ��������, World�� TimManager�� DeltaTime���� ����ؾ� �ɰ� ����
template<typename T>
inline void World::SetTimer(T* owner, void(T::* func)(), float wait)
{
	std::unique_ptr<Timer> timer = std::make_unique<Timer>(wait);
	timer->_execute = [owner, func]() {
		// ���� �ð� ���Ŀ�
		while (!timer->TimerTick(GetWorldTimer().GetDeltaTime())) {}
			// �Լ� �����ͷ� ���� �Լ� ����
			(owner->*func)();
	};
}