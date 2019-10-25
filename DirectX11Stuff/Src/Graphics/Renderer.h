#pragma once
#include <D3D11.h>
#include <D3DX10.h>
#include <D3DX11.h>

#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DX10.lib")
#pragma comment(lib, "D3DX11.lib")

class Renderer
{
public:
	bool Init();

	void Clear(D3DXCOLOR color);
	void Present(bool vSync);

	void Shutdown();

private:
	//Basic DirectX
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11RenderTargetView* RenderTargetView = nullptr;

	//Depth Stencil
	ID3D11DepthStencilState* DepthStencilState = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	ID3D11Texture2D* DepthStencilBuffer = nullptr;

	//Rasterizer
	ID3D11RasterizerState* RasterizerState = nullptr;
};