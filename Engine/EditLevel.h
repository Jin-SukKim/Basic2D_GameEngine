#pragma once
#include "Level.h"
class EditLevel : public Level
{
public:
	EditLevel();
	virtual ~EditLevel();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render(HDC hdc) override;

private:
	void DrawLine();
	void StopDraw();
	bool SaveDrawing(const std::wstring& file);
	bool LoadDrawing(const std::wstring& file);
	void Undo();
	void Clear();
private:
	// TODO: Line이 아니라 Mesh Class를 따로 파서 원, 박스같은 형태도 그릴 수 있도록
	std::vector<std::pair<POINT, POINT>> _lines;

	fs::path _resourcePath;

	bool _setOrigin = true;
	POINT _lastPos = {};
};

