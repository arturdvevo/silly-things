#include <windows.h>
#include <stdio.h>
#include <wingdi.h>

#pragma comment(lib, "gdi32.lib")

#define ID_MY_WINDOW_CLASS "MyWindowClass"
#define CENTER_X 100
#define CENTER_Y 100
#define RADIUS 50

void DrawCircle(HDC hdc, int centerX, int centerY, int radius)
{
    int left = centerX - radius;
    int top = centerY - radius;
    int right = centerX + radius;
    int bottom = centerY + radius;

    Ellipse(hdc, left, top, right, bottom);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register window class
    WNDCLASS wc = {0};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = ID_MY_WINDOW_CLASS;
    RegisterClass(&wc);

    // Create window
    HWND hWnd = CreateWindowEx(
        0,
        ID_MY_WINDOW_CLASS,
        "My Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hWnd == NULL)
    {
        // Display an error message and gracefully exit
        MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterClass(ID_MY_WINDOW_CLASS, wc.hInstance);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Draw the circle
            DrawCircle(hdc, CENTER_X, CENTER_Y, RADIUS);

            EndPaint(hwnd, &ps);
            ReleaseDC(hwnd, hdc);
            break;
        }

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}