#pragma once

#ifdef CreateWindow
#undef CreateWindow
#endif

class Window
{
public:
	bool Init(const WNDPROC& wndproc);
	void Shutdown();

private:
	HWND hWND;
	WNDCLASSEX WC;
};