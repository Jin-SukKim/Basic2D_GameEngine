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
	// TODO: Line�� �ƴ϶� Mesh Class�� ���� �ļ� ��, �ڽ����� ���µ� �׸� �� �ֵ���
	std::vector<std::pair<POINT, POINT>> _lines;

	fs::path _resourcePath;

	bool _setOrigin = true;
	POINT _lastPos = {};
};

