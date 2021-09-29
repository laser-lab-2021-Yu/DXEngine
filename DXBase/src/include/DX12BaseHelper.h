
// 参考：https://bit.ly/3EUPEKD

#pragma once

#include <stdexcept>

//--------------------------------------------------------------------------------------------
// 
// 主に使用するもの
// 
//--------------------------------------------------------------------------------------------

// CPU上のリソース管理を行うスマートポインタ
// NOTE: GPU上のリソース管理については受け付けないので自分で行う
using Microsoft::WRL::ComPtr;

namespace std
{
    // UNICODE対応  : std::tstring = std::wstring
    // UNICODE非対応: std::tstring = std::string
    using tstring = basic_string<TCHAR>;
}

// HRESULT型のエラーを受け取ったら、例外を投げる
void ThrowIfFailed(HRESULT hr);

//--------------------------------------------------------------------------------------------
// 
// 以下は各種定義
// 
//--------------------------------------------------------------------------------------------

#pragma region HRESULT型のエラーを例外として扱うコード

inline std::string HrToString(HRESULT hr)
{
    char str[64] = {};
    sprintf_s(str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
    return std::string(str);
}

class HrException : public std::runtime_error
{
public:

    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), _hr(hr) {}
    HRESULT GetError() const { return _hr; }

private:

    const HRESULT _hr;
};

inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr)) throw HrException(hr);
}

#pragma endregion HRESULT型のエラーを例外として扱うコード
