#include "PCH.h"
#include "Graphics/Renderer.h"

#ifdef _DEBUG
UINT flags = D3D11_CREATE_DEVICE_DEBUG;
#else
UINT flags = 0;
#endif

template<typename T>
static void SAFE_RELEASE(T& ptr)
{
	HRESULT Result = 0;

	if (ptr != nullptr)
	{
		Result = ptr->Release();
		if (FAILED(Result))
		{
			LOG_ERROR("Failed to release COM object");
		}

		ptr = nullptr;
	}
}

bool Renderer::Init(Window* window)
{
	HRESULT Result = 0;
	
	//Create our swap chain buffer description
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = window->mWidth;
	bufferDesc.Height = window->mHeight;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Create swap chain description
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferDesc = bufferDesc;
	scd.BufferCount = 1;
	scd.OutputWindow = window->hWND;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.SampleDesc.Count = 4;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//Create our swap chain and device
	Result = D3D11CreateDeviceAndSwapChain(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		flags,
		0,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&SwapChain,
		&Device,
		0,
		&Context);

	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create swap chain");
		return(false);
	}

	//Create our BackBuffer
	ID3D11Texture2D* BackBuffer;
	Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& BackBuffer);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create back buffer");
		return(false);
	}

	//Create our Render Target
	Result = Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTargetView);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create render target");
		return(false);
	}

	SAFE_RELEASE(BackBuffer);

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.Width = window->mWidth;
	depthStencilDesc.Height = window->mHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
	ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	depthStencilStateDesc.StencilEnable = TRUE;
	depthStencilStateDesc.StencilReadMask = 0xFF;
	depthStencilStateDesc.StencilWriteMask = 0xFF;

	depthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Result = Device->CreateDepthStencilState(&depthStencilStateDesc, &DepthStencilState);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create depth stencil state");
		return(false);
	}

	Result = Device->CreateTexture2D(&depthStencilDesc, 0, &DepthStencilBuffer);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create depth stencil buffer");
		return(false);
	}

	Result = Device->CreateDepthStencilView(DepthStencilBuffer, 0, &DepthStencilView);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create depth stencil view");
		return(false);
	}

	Context->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
	Context->OMSetDepthStencilState(DepthStencilState, 1);

	//Rasterizer
	D3D11_RASTERIZER_DESC RastDesc;
	ZeroMemory(&RastDesc, sizeof(D3D11_RASTERIZER_DESC));
	RastDesc.FillMode = D3D11_FILL_SOLID;
	RastDesc.CullMode = D3D11_CULL_NONE;
	RastDesc.MultisampleEnable = true;
	RastDesc.AntialiasedLineEnable = true;

	Result = Device->CreateRasterizerState(&RastDesc, &RasterizerState);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to create rasterizer state");
		return(false);
	}

	Context->RSSetState(RasterizerState);

	//Create our viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Width = window->mWidth;
	viewport.Height = window->mHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &viewport);

	return(true);
}

void Renderer::Clear(float r, float g, float b, float a)
{
	Context->ClearRenderTargetView(RenderTargetView, D3DXCOLOR(r, g, b, a));
	Context->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Renderer::Present(bool vSync)
{
	HRESULT Result = 0;
	Result = SwapChain->Present(vSync, 0);
	if (FAILED(Result))
	{
		LOG_ERROR("Failed to present back buffer");
	}
}

void Renderer::Shutdown()
{
	SwapChain->SetFullscreenState(0, 0);

	SAFE_RELEASE(RasterizerState);
	SAFE_RELEASE(DepthStencilBuffer);
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(SwapChain);
	SAFE_RELEASE(DepthStencilState);
	SAFE_RELEASE(Context);
	SAFE_RELEASE(Device);
}