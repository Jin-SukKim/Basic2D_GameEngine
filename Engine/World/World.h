#pragma once

class TimeManager;
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

	/* 
	* Timer�� TimeManager�� ����°� �´°� ����
	// function_ptr�� function�� �޾� �����ð� �ڿ� ������ �� �ֵ���
	template<typename T>
	void SetTimer(T* owner, void(T::* func)(), float wait); // T type�� void() �Լ� �����͸� �޴´�.
	*/
public:
	static Vector2D GetCameraPos() { return _worldCamera; }
	static void SetCameraPos(Vector2D pos) { _worldCamera = pos; }

	static void SetCurrentLevel(std::shared_ptr<Level> level) { _curLevel = level; }
	static std::shared_ptr<Level> GetCurrentLevel() { return _curLevel; }
private:
	std::unique_ptr<TimeManager> _timeManager;
	std::unique_ptr<LevelManager> _levelManager = nullptr;

	inline static std::shared_ptr<Level> _curLevel = nullptr;

	inline static Vector2D _worldCamera = { 400, 300 };
};
/*
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
*/