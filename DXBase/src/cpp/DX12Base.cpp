#include "..\include\DX12Base.h"

DX12Base::DX12Base(std::tstring name, int width, int height) :
    _title(name),
    _width(width),
    _height(height),
    _aspectRatio(static_cast<float>(width)/static_cast<float>(height))
{
}

DX12Base::~DX12Base()
{
}

bool DX12Base::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    {
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(hWnd);
        }
        return true;
    }
    }
    return false;
}

void DX12Base::GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter)
{
    *ppAdapter = nullptr;
    ComPtr<IDXGIAdapter1> selectedAdapter;

    ComPtr<IDXGIFactory6> factory6;
    // GPU�ɋ��߂����'gpuPreference'�𖞂���GPU�������B
    if (SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6))))
    {
        auto gpuPreference = (requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED);
        for (
            UINT adapterIndex = 0U;
            SUCCEEDED(factory6->EnumAdapterByGpuPreference(adapterIndex, gpuPreference, IID_PPV_ARGS(&selectedAdapter)));
            ++adapterIndex)
        {
            DXGI_ADAPTER_DESC1 desc;
            selectedAdapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // D3D12�ɑΉ����Ă��邩�ǂ����`�F�b�N���邾���B�f�o�C�X�̍쐬�͍s��Ȃ��B
            if (SUCCEEDED(D3D12CreateDevice(selectedAdapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
            {
                break;
            }
        }
    }

    // GPU�ɋ��߂����'gpuPreference'�𖞂����Ȃ������ꍇ�A���̏����𖳎����Č����B
    if (selectedAdapter.Get() == nullptr)
    {
        for (UINT adapterIndex = 0U; SUCCEEDED(pFactory->EnumAdapters1(adapterIndex, &selectedAdapter)); ++adapterIndex)
        {
            DXGI_ADAPTER_DESC1 desc;
            selectedAdapter->GetDesc1(&desc);

            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
            {
                // Don't select the Basic Render Driver adapter.
                // If you want a software adapter, pass in "/warp" on the command line.
                continue;
            }

            // D3D12�ɑΉ����Ă��邩�ǂ����`�F�b�N���邾���B�f�o�C�X�̍쐬�͍s��Ȃ��B
            if (SUCCEEDED(D3D12CreateDevice(selectedAdapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
            {
                break;
            }
        }
    }

    *ppAdapter = selectedAdapter.Detach();
}
