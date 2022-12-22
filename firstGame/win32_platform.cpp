#include<Windows.h>
#include "util.cpp";

bool running = true;

struct RenderState {
	s32 height, width;
	void* memory;

	BITMAPINFO bitmapinfo;
};

RenderState render_state;

#include "platform_common.cpp";
#include "renderer.cpp";
#include "game.cpp";

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	LRESULT result = 0;

	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		s32 size = render_state.width * render_state.height * sizeof(u32);

		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
		render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
		render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
		render_state.bitmapinfo.bmiHeader.biPlanes = 1;
		render_state.bitmapinfo.bmiHeader.biBitCount = 32;
		render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;



	} break;
	default:{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return result;
	}
};

s32 WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, s32 nShowCmd) {
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
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.016666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float perfomance_frequency;
	{
		LARGE_INTEGER pref;
		QueryPerformanceFrequency(&pref);
		perfomance_frequency = (float)pref.QuadPart;
	}

	while (running) {
		//input
		for (s32 i = 0; i < BUTTON_COUNT; i++)
		{
			input.buttons[i].changed = false;
		}

		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE)) {

			switch (msg.message) {
				case WM_KEYUP:
				case WM_KEYDOWN: {
					u32 vk_code = (u32)msg.wParam;
					bool is_down = ((msg.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].is_down = is_down;\
input.buttons[b].changed = true;\
} break;

					switch (vk_code)
					{
						process_button(BUTTON_UP, VK_UP);
						process_button(BUTTON_DOWN, VK_DOWN);
						process_button(BUTTON_RIGHT, VK_RIGHT);
						process_button(BUTTON_LEFT, VK_LEFT);
					}
				
				} break;
				default:{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}

		//simutalte
		simulate_game(&input, delta_time);

		//render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / perfomance_frequency;
		frame_begin_time = frame_end_time;

	}
};