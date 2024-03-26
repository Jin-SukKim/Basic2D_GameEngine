#include "pch.h"
#include "EngineWindow.h"

EngineWindow* win = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return win->WinProc(hwnd, uMsg, wParam, lParam);
}

EngineWindow::EngineWindow()
{
	win = this;
}

EngineWindow::~EngineWindow()
{
	win = nullptr;
}

bool EngineWindow::InitWin(HINSTANCE& hInstance, int& nCmdShow)
{
    // 1) 윈도우 창 정보 등록
    if (!RegisterWindowClass(hInstance))
        return false;

    // 2) 윈도우 창 생성
    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
        return false;

    SetDoubleBuffering(_hwnd);

    return true;
}

bool EngineWindow::RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // 이벤트를 처리할 일종의 함수 포인터
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"Engine";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

    // 윈도우 클래스 등록
    return ::RegisterClassExW(&wcex);
}

bool EngineWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _hInst = hInstance; // Store instance handle in our global variable

    // 윈도우 메뉴바를 제외하고 캔버스 사이즈를 지정
    RECT windowRect = { 0, 0, _screenWidth, _screenHeight };
    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

    // 등록한 윈도우 클래스로 윈도우창 생성
    HWND hWnd = ::CreateWindowW(L"Engine", L"Client", WS_OVERLAPPEDWINDOW,
        1480, 370, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return false;
    }

    _hwnd = hWnd;

    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    SetDoubleBuffering(hWnd);

    // Engine
    if (!Init())
        return false;

    return true;
}

void EngineWindow::SetDoubleBuffering(HWND hWnd)
{
    _hdc = ::GetDC(hWnd);

    // 윈도우 창 캔버스 크기
    ::GetClientRect(hWnd, &_rect);

    // _hdc와 호환되는 DC 생성 
    _hdcBack = ::CreateCompatibleDC(_hdc);
    // _hdc와 호환되는 비트맵 생성
    _bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    // DC와 BMP 연결
    HBITMAP prev = static_cast<HBITMAP>(::SelectObject(_hdcBack, _bmpBack));
    ::DeleteObject(prev); // 이전 BitMap 삭제
}

int EngineWindow::Run()
{
    MSG msg = {};

    // 3) 메인 루프
    //  - 입력
    //  - 로직
    //  - 렌더링
    // 
    // Main message loop:
    while (msg.message != WM_QUIT)
    {
        // Message Event 처리 (msg가 있을때만)
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else {

            // Engine
            Tick();
            Render();

            DoubleBuffering();
        }
    }

    return (int)msg.wParam;
}


void EngineWindow::DoubleBuffering()
{
    // BitBlt(BitBullet) : 고속 복사 (memcpy와 같다)
    ::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY); // render
    ::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS); // remove   
}

LRESULT EngineWindow::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case 105:
            ::DestroyWindow(hWnd);
            break;
        default:
            return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_PAINT: // render (WM_PAINT는 한 번만 그려준다.)
    {
        PAINTSTRUCT ps;
        // 일종의 식별번호
        HDC hdc = ::BeginPaint(hWnd, &ps); // hdc = handle device context

        ::EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        // ESC 누르면 프로그램 종료
        if (wParam == 27)
            DestroyWindow(hWnd);
        break;
    case WM_MOUSEMOVE: // 마우스 좌표
        // int lParam인 32bit에서 뒤 16bit는 x값, 앞 16bit는 y값으로 사용
        // lParam & 0xFFFF;
        _mousePosX = LOWORD(lParam);
        // (lParam >> 16) & 0xFFFF;
        _mousePosY = HIWORD(lParam);
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    default:
        return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

