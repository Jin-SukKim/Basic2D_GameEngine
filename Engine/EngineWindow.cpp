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
    // 1) ������ â ���� ���
    if (!RegisterWindowClass(hInstance))
        return false;

    // 2) ������ â ����
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
    wcex.lpfnWndProc = WndProc; // �̺�Ʈ�� ó���� ������ �Լ� ������
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(107));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"Engine";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(108));

    // ������ Ŭ���� ���
    return ::RegisterClassExW(&wcex);
}

bool EngineWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    _hInst = hInstance; // Store instance handle in our global variable

    // ������ �޴��ٸ� �����ϰ� ĵ���� ����� ����
    RECT windowRect = { 0, 0, _screenWidth, _screenHeight };
    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

    // ����� ������ Ŭ������ ������â ����
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

    // ������ â ĵ���� ũ��
    ::GetClientRect(hWnd, &_rect);

    // _hdc�� ȣȯ�Ǵ� DC ���� 
    _hdcBack = ::CreateCompatibleDC(_hdc);
    // _hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
    _bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);
    // DC�� BMP ����
    HBITMAP prev = static_cast<HBITMAP>(::SelectObject(_hdcBack, _bmpBack));
    ::DeleteObject(prev); // ���� BitMap ����
}

int EngineWindow::Run()
{
    MSG msg = {};

    // 3) ���� ����
    //  - �Է�
    //  - ����
    //  - ������
    // 
    // Main message loop:
    while (msg.message != WM_QUIT)
    {
        // Message Event ó�� (msg�� ��������)
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
    // BitBlt(BitBullet) : ��� ���� (memcpy�� ����)
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
    case WM_PAINT: // render (WM_PAINT�� �� ���� �׷��ش�.)
    {
        PAINTSTRUCT ps;
        // ������ �ĺ���ȣ
        HDC hdc = ::BeginPaint(hWnd, &ps); // hdc = handle device context

        ::EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        // ESC ������ ���α׷� ����
        if (wParam == 27)
            DestroyWindow(hWnd);
        break;
    case WM_MOUSEMOVE: // ���콺 ��ǥ
        // int lParam�� 32bit���� �� 16bit�� x��, �� 16bit�� y������ ���
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

