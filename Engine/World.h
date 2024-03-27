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

	// function_ptr로 function을 받아 일정시간 뒤에 실행할 수 있도록
	template<typename T>
	void SetTimer(T* owner, void(T::* func)(), float wait); // T type의 void() 함수 포인터를 받는다.
private:
	std::unique_ptr<TimeManager> _timeManager;
};

// TODO: Thread로 돌리던지, World의 TimManager의 DeltaTime값을 사용해야 될것 같다
template<typename T>
inline void World::SetTimer(T* owner, void(T::* func)(), float wait)
{
	std::unique_ptr<Timer> timer = std::make_unique<Timer>(wait);
	timer->_execute = [owner, func]() {
		// 일정 시간 이후에
		while (!timer->TimerTick(GetWorldTimer().GetDeltaTime())) {}
			// 함수 포인터로 받은 함수 실행
			(owner->*func)();
	};
}