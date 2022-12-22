#include<Windows.h>
#include<iostream>
using namespace std;

bool running = true;
LRESULT result = 0;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;
	{
	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return result;
	}
};

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	const wchar_t window_title[] = L"My First Game!";

	//create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = CLASS_NAME;
	window_class.lpfnWndProc = window_callback;
	//register class
	RegisterClass(&window_class);
	//create window
	HWND window = CreateWindow(window_class.lpszClassName,window_title,WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,1200,600,0,0,hInstance,0);

	while (running) {
		//input
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
		//simutalte

		//render
};