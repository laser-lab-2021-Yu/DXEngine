#pragma once

#ifndef DECLSPEC_SELECTANY
#	define DECLSPEC_SELECTANY __declspec(selectany)
#endif

#ifdef DXAPPLICATION_EXPORTS
#	define DXAPP_API __declspec(dllexport)
#else
#	define DXAPP_API __declspec(dllimport)
#endif

class DX12Base;

class DXAPP_API Win32Application
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
