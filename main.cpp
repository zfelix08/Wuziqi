#include <iostream>
#include <windows.h>

struct WindowProperties
{
    bool isRunning = true;
    int cursorX;
    int cursorY;
};

WindowProperties wProperties;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            if (MessageBox(hwnd, "Are you sure you want to ext?", "Wuziqi", MB_YESNO) == IDYES)
            {
                wProperties.isRunning = false;
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main()
{
    WNDCLASS wc = {sizeof(WNDCLASS)};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "WindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        std::cerr << "Failed to register window class." << std::endl;
        return -1;
    }

    wProperties.isRunning = true;

    HWND hwnd = CreateWindowA(
        wc.lpszClassName,
        "Wuziqi",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        nullptr, nullptr, wc.hInstance, nullptr);

    while (wProperties.isRunning)
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}