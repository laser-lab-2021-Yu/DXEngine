
#include <Win32Application.h>
#include <DX12Base.h>
#include <DX12HelloImGui.h>

int Win32Application::Run(DX12Base* pApp, HINSTANCE hInst, int nCmdShow)
{
	WNDCLASSEX wndClassEx = {};
	{
		wndClassEx.cbSize		 = sizeof(WNDCLASSEX);
		wndClassEx.style		 = CS_HREDRAW | CS_VREDRAW;
		wndClassEx.lpfnWndProc	 = WindowProc;
		wndClassEx.hInstance	 = hInst;
		wndClassEx.hCursor		 = LoadCursor(nullptr, IDC_ARROW);
		wndClassEx.lpszClassName = _T("DX12Base");
	}
	RegisterClassEx(&wndClassEx);

	RECT wndRect = { 0L, 0L, static_cast<LONG>(pApp->GetWidth()), static_cast<LONG>(pApp->GetHeight()) };
	AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̍쐬
	_hWnd = CreateWindow(
		wndClassEx.lpszClassName,
		pApp->GetTitle(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top,
		nullptr, // �e�E�B���h�E�͎����Ȃ�
		nullptr, // ���j���[�͎����Ȃ�
		wndClassEx.hInstance,
		pApp // �A�v���P�[�V�����ւ̃|�C���^��GW_USERDATA�Ƃ��ăE�B���h�E�ɕۊǂ���
	);
	ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));

	// �A�v���P�[�V�����̏������B
	// �����'pApp'�ɓn�����|�C���^�ɂ���ĕω�����B
	pApp->OnInit();

	ShowWindow(_hWnd, nCmdShow);
	UpdateWindow(_hWnd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// �A�v���P�[�V�����̌�Еt���B
	// �����'pApp'�ɓn�����|�C���^�ɂ���ĕω�����B
	pApp->OnDestroy();

	return static_cast<char>(msg.wParam);
}

LRESULT CALLBACK Win32Application::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (DX12Base* temp = reinterpret_cast<DX12Base*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
	{
		if (temp->MsgProc(hWnd, msg, wParam, lParam)) return 0;
	}

	switch (msg)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		return 0;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
