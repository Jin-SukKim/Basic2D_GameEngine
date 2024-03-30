#pragma once
class EngineWindow
{
public:
	EngineWindow();
	~EngineWindow();

	bool InitWin(HINSTANCE& hInstance, int& nCmdShow);
	int Run();
	virtual LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual bool Init() = 0;
	virtual void Tick() = 0;
	virtual void Render() = 0;

	void SetWindowSize(const int32& width, const int32& height) { 
		_screenWidth = width; 
		_screenHeight = height;
	};

	static std::tuple<int32, int32> GetScreenSize() {
		return { _screenWidth, _screenHeight };
	}
	static int32 GetScreenWidth() {	return _screenWidth; }
	static int32 GetScreenHeight() { return _screenHeight; }

	std::tuple<int32, int32> GetMousePos() const {
		return { _mousePosX, _mousePosY };
	}
	int32 GetMouseX() const { return _mousePosX; }
	int32 GetMouseY() const { return _mousePosY; }
private:
	// 1) ������ â ���� ���
	bool RegisterWindowClass(HINSTANCE hInstance);

	// 2) ������ â ����
	// Perform application initialization:
	bool InitInstance(HINSTANCE hInstance, int nCmdShow);
	void SetDoubleBuffering(HWND hWnd);
	FORCEINLINE void DoubleBuffering();

protected:
	/*
		HINSTANCE = �ڵ� �ν��Ͻ�, ���α׷��� �ν��Ͻ� �ĺ���, ���� ���� ���α׷� ��ü�� ��üȭ�� �ּ�.
		��� = HINSTANCE�� ���α׷� ��ü�� �ڵ��̸� , HWND�� ���α׷����� ������â�� ��ȣ
	*/
	HINSTANCE _hInst = {};
	// ������ �ڵ� (������â�� �ڵ� ��ȣ)
	HWND _hwnd = {};
	// DC�� ��¿� �ʿ��� ������ ������ ������ ���� (��ǥ, �� ��)
	// HDC�� DC�� ������ �����ϴ� ������ ����ü�� �޸� �ּҸ� ����Ű�� ��
	HDC _hdc = {}; // ���⼭ ������
	// Double Buffering
	RECT _rect = {};
	HDC _hdcBack = {}; // ���⿡ �׸���
	HBITMAP _bmpBack = {};

	int32 _mousePosX = 0;
	int32 _mousePosY = 0;

	static int32 _screenWidth;
	static int32 _screenHeight;
};

