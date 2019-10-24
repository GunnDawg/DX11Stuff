#pragma once

#ifdef CreateWindow
#undef CreateWindow
#endif

struct Window
{
	bool Init(u16 width, u16 height, WNDPROC wndproc);
	void Shutdown();

	HWND hWND;
	WNDCLASSEX WC;
	u16 mWidth;
	u16 mHeight;
};