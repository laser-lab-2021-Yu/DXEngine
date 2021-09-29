#pragma once

#ifdef DX12HELLOIMGUI_EXPORTS
#	define DX12HELLOIMGUI_API __declspec(dllexport)
#else
#	define DX12HELLOIMGUI_API __declspec(dllimport)
#endif

#include <DX12Base.h>

class DX12HELLOIMGUI_API DX12HelloImGui : public DX12Base
{
public:

	DX12HelloImGui(std::tstring name, int width, int height);
	virtual ~DX12HelloImGui();

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnDestroy();

private:

	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
    void WaitForPreviousFrame();

    // 総フレーム数
    static const UINT kFrameCount = 2U;

    // パイプラインオブジェクト
    CD3DX12_VIEWPORT                  _viewport;
    CD3DX12_RECT                      _scissorRect;
    ComPtr<ID3D12Device>              _device;
    ComPtr<ID3D12CommandQueue>        _cmdQueue;
    ComPtr<IDXGISwapChain4>           _swapChain;
    ComPtr<ID3D12DescriptorHeap>      _rtvHeap;
    ComPtr<ID3D12Resource>            _backBuffers[kFrameCount];
    ComPtr<ID3D12CommandAllocator>    _cmdAlloc;
    ComPtr<ID3D12RootSignature>       _rootSignature;
    ComPtr<ID3D12PipelineState>       _pipelineState;
    ComPtr<ID3D12GraphicsCommandList> _cmdList;

    // 同期処理に必要なオブジェクト
    UINT                _frameIndex;
    HANDLE              _fenceEvent;
    ComPtr<ID3D12Fence> _fence;
    UINT64              _fenceValue;
};

#ifndef DX12HELLOIMGUI_EXPORTS
#	pragma comment(lib, "DX12HelloImGui.lib")
#endif
