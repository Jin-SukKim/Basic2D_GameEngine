#pragma once
#include "TimeManager.h"
#include "Timer.h"

class LevelManager;
class Level;

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
	std::unique_ptr<LevelManager> _levelManager;
};

// TODO: Thread�� ��������, World�� TimManager�� DeltaTime���� ����ؾ� �ɰ� ����
// ���ο� ���̵�� : wait time�� �������� priority_queue�� ��� tick���� sumTime ���� ���� ���
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