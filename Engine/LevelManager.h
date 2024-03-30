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
	void SetLevel(std::unique_ptr<Level> level);

private:
	std::unique_ptr<class Level> _level;
	LevelType _levelType = LevelType::LEVEL_DEFAULT;
};
