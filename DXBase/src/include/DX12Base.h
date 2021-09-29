
// 参考：https://bit.ly/3ib4umj

#pragma once

#include "DX12BaseHelper.h"

#ifdef DXBASE_EXPORTS
#	define DXBASE_API __declspec(dllexport)
#else
#	define DXBASE_API __declspec(dllimport)
#endif

class DXBASE_API DX12Base
{
public:

	DX12Base(std::tstring name, int width, int height);
	virtual ~DX12Base();

	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnDestroy() = 0;

	virtual bool MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// アクセッサ
	int		GetWidth() const		{ return _width; }
	int		GetHeight() const		{ return _height; }
	float	GetAspectRatio() const	{ return _aspectRatio; }
	LPCTSTR GetTitle() const		{ return _title.c_str(); }

protected:

	void GetHardwareAdapter(
		_In_ IDXGIFactory1* pFactory,
		_Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
		bool requestHighPerformanceAdapter = false);

private:

	// ビューポートパラメータ
	int   _width;
	int   _height;
	float _aspectRatio;

	// ウィンドウのタイトル名
	std::tstring _title;
};

#ifndef DXBASE_EXPORTS
#	pragma comment(lib, "DX12Base.lib")
#endif
