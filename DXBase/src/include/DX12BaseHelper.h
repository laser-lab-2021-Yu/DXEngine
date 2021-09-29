
// �Q�l�Fhttps://bit.ly/3EUPEKD

#pragma once

#include <stdexcept>

//--------------------------------------------------------------------------------------------
// 
// ��Ɏg�p�������
// 
//--------------------------------------------------------------------------------------------

// CPU��̃��\�[�X�Ǘ����s���X�}�[�g�|�C���^
// NOTE: GPU��̃��\�[�X�Ǘ��ɂ��Ă͎󂯕t���Ȃ��̂Ŏ����ōs��
using Microsoft::WRL::ComPtr;

namespace std
{
    // UNICODE�Ή�  : std::tstring = std::wstring
    // UNICODE��Ή�: std::tstring = std::string
    using tstring = basic_string<TCHAR>;
}

// HRESULT�^�̃G���[���󂯎������A��O�𓊂���
void ThrowIfFailed(HRESULT hr);

//--------------------------------------------------------------------------------------------
// 
// �ȉ��͊e���`
// 
//--------------------------------------------------------------------------------------------

#pragma region HRESULT�^�̃G���[���O�Ƃ��Ĉ����R�[�h

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

#pragma endregion HRESULT�^�̃G���[���O�Ƃ��Ĉ����R�[�h
