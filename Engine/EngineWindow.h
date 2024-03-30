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
	// 1) 윈도우 창 정보 등록
	bool RegisterWindowClass(HINSTANCE hInstance);

	// 2) 윈도우 창 생성
	// Perform application initialization:
	bool InitInstance(HINSTANCE hInstance, int nCmdShow);
	void SetDoubleBuffering(HWND hWnd);
	FORCEINLINE void DoubleBuffering();

protected:
	/*
		HINSTANCE = 핸들 인스턴스, 프로그램의 인스턴스 식별자, 쉽게 보면 프로그램 자체의 실체화된 주소.
		결론 = HINSTANCE는 프로그램 자체의 핸들이며 , HWND는 프로그램안의 윈도우창의 번호
	*/
	HINSTANCE _hInst = {};
	// 윈도우 핸들 (윈도우창의 핸들 번호)
	HWND _hwnd = {};
	// DC는 출력에 필요한 정보를 가지는 데이터 구조 (좌표, 색 등)
	// HDC는 DC의 정보를 저장하는 데이터 구조체의 메모리 주소를 가르키는 값
	HDC _hdc = {}; // 여기서 렌더링
	// Double Buffering
	RECT _rect = {};
	HDC _hdcBack = {}; // 여기에 그리기
	HBITMAP _bmpBack = {};

	int32 _mousePosX = 0;
	int32 _mousePosY = 0;

	static int32 _screenWidth;
	static int32 _screenHeight;
};

