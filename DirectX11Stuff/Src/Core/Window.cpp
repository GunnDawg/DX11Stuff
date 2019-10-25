#include "PCH.h"
#include "Core/Window.h"

bool Window::Init(const WNDPROC& wndproc)
{
	ZeroMemory(&WC, sizeof(WNDCLASSEX));
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.hbrBackground = HBRUSH(COLOR_WINDOW);
	WC.hCursor = LoadCursor(0, IDC_ARROW);
	WC.hInstance = GetModuleHandle(0);
	WC.lpfnWndProc = wndproc;
	WC.lpszClassName = "WindowClass";
	WC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&WC))
	{
		LOG_ERROR("Failed to register window class");
		return(false);
	}

	hWND = CreateWindowEx(
		0,
		WC.lpszClassName,
		"DirectX11 Stuff",
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GameSettings::Display::Width,
		GameSettings::Display::Height,
		0,
		0,
		GetModuleHandle(0),
		0);

	if (!hWND)
	{
		LOG_ERROR("Failed to create window");
		return(false);
	}

	return(true);
}

void Window::Shutdown()
{
	if (hWND)
	{
		DestroyWindow(hWND);
		hWND = nullptr;

		UnregisterClass(WC.lpszClassName, GetModuleHandle(0));
	}
}