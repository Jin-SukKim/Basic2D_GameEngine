#pragma once

class Level;

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void Init();
	void Tick(float DeltaTime);
	void Render(HDC hdc);

public:
	void ChangeLevel(LevelType levelType);
	void SetLevel(std::shared_ptr<Level> level);

	std::shared_ptr<Level> GetCurrentLevel() const { return _level; }
private:
	std::shared_ptr<Level> _level;
	LevelType _levelType = LevelType::LEVEL_DEFAULT;
};
