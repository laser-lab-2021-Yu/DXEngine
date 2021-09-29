#pragma once

#ifndef DECLSPEC_SELECTANY
#	define DECLSPEC_SELECTANY __declspec(selectany)
#endif

class DX12Base;
class Win32Application
{
public:

	static int	Run(DX12Base* pApp, HINSTANCE hInst, int nCmdShow);
	static HWND GetHWND() { return _hWnd; }

protected:

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:

	static HWND _hWnd;
};

DECLSPEC_SELECTANY HWND Win32Application::_hWnd = nullptr;
