#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>
#include <wrl.h> // ComPtr

#include <d3dx12.h>
#include <dxgi1_6.h>	 // IDXGIFactory6
#include <d3dcompiler.h> // D3DCompileFromFile
#include <DirectXMath.h>

#include <tchar.h> // std::tstring
#include <cstring> // std::tstring

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
