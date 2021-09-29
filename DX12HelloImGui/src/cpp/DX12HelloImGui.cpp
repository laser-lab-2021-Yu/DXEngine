
#include <DX12HelloImGui.h>

DX12HelloImGui::DX12HelloImGui(std::tstring name, int width, int height) :
	DX12Base(name, width, height),
	_frameIndex(0U),
	_viewport(0U, 0U, static_cast<FLOAT>(width), static_cast<FLOAT>(height)),
	_scissorRect(0L, 0L, static_cast<LONG>(width), static_cast<LONG>(height))
{
}

DX12HelloImGui::~DX12HelloImGui()
{
}

void DX12HelloImGui::OnInit()
{
	LoadPipeline();
	LoadAssets();
}

void DX12HelloImGui::OnUpdate()
{
}

void DX12HelloImGui::OnRender()
{
	// 描画に必要な命令を割り当てる
	PopulateCommandList();

	// 命令の実行
	ID3D12CommandList* ppCmdLists[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(ppCmdLists), ppCmdLists);

	// フレームの切り替え
	ThrowIfFailed(_swapChain->Present(1U, 0U));

	WaitForPreviousFrame();
}

void DX12HelloImGui::OnDestroy()
{
	// デストラクタによる後片付け中のリソースを、GPUが参照することを防止。
	WaitForPreviousFrame();
	CloseHandle(_fenceEvent);
}

void DX12HelloImGui::LoadPipeline()
{
}

void DX12HelloImGui::LoadAssets()
{
}

void DX12HelloImGui::PopulateCommandList()
{
	// メモリ再利用のためリセット
	ThrowIfFailed(_cmdAlloc->Reset());
	ThrowIfFailed(_cmdList->Reset(_cmdAlloc.Get(), _pipelineState.Get()));

	_cmdList->SetGraphicsRootSignature(_rootSignature.Get());
	_cmdList->RSSetViewports(1U, &_viewport);
	_cmdList->RSSetScissorRects(1U, &_scissorRect);

	// バックバッファをレンダーターゲットとして扱う
	CD3DX12_RESOURCE_BARRIER barrier = {};
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(_backBuffers[_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	_cmdList->ResourceBarrier(1U, &barrier);

	UINT rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(_rtvHeap->GetCPUDescriptorHandleForHeapStart(), _frameIndex, rtvDescriptorSize);
	_cmdList->OMSetRenderTargets(1U, &rtvHandle, FALSE, nullptr);

	// フレーム全体を'clearColor'で塗りつぶす
	const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	_cmdList->ClearRenderTargetView(rtvHandle, clearColor, 0U, nullptr);

	// あとはフレームの切り替えを待つのみ
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(_backBuffers[_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	_cmdList->ResourceBarrier(1U, &barrier);

	// 命令の追加を受け入れなくする
	ThrowIfFailed(_cmdList->Close());
}

void DX12HelloImGui::WaitForPreviousFrame()
{
	const UINT64 fence = _fenceValue;
	ThrowIfFailed(_cmdQueue->Signal(_fence.Get(), fence));
	++_fenceValue;

	// 直前のフレーム処理が終わるのを待つ
	if (_fence->GetCompletedValue() < fence)
	{
		ThrowIfFailed(_fence->SetEventOnCompletion(fence, _fenceEvent));
		WaitForSingleObject(_fenceEvent, INFINITE);
	}

	_frameIndex = _swapChain->GetCurrentBackBufferIndex();
}
