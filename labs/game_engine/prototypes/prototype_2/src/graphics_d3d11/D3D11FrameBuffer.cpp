#include "graphics_pch.h"
#include "D3D11FrameBuffer.h"
#include "D3D11RenderTarget.h"

namespace engine
{
	D3D11FrameBuffer::D3D11FrameBuffer(void)
	{
		m_pDevice			= NULL;

		m_pSwapChain		= NULL;

		

		m_pContext			= NULL;

		m_clearColor		= math::Color4();
		m_clearDepth		= 1.0f;
		m_clearStencil		= 0;
	}


	D3D11FrameBuffer::~D3D11FrameBuffer(void)
	{
	}
	bool D3D11FrameBuffer::Initialize(ID3D11Device* pDevice, const GraphicsParameters& param)
	{
		m_pDevice = pDevice;

		if(m_pDevice == NULL)
		{
			return false;

		}

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof(sd) );

		sd.BufferCount										= 2;
		sd.BufferDesc.Width									= param.width;
		sd.BufferDesc.Height								= param.height;
		sd.BufferDesc.Format								= DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator					= 60;
		sd.BufferDesc.RefreshRate.Denominator				= 1;
		sd.BufferUsage										= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow										= (HWND)param.wnd;
		sd.SampleDesc.Count									= 1;
		sd.SampleDesc.Quality								= 0;
		sd.Windowed											= TRUE;
		sd.SwapEffect										= DXGI_SWAP_EFFECT_SEQUENTIAL;


		IDXGIFactory1* pFactory = NULL;

		IDXGIDevice* pDXGIDevice = NULL;

		HRESULT ret = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
		if(FAILED(ret))
		{
			return false;
		}

		IDXGIAdapter * pDXGIAdapter;
		ret = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);


		if(FAILED(ret))
		{
			return false;
		}


		ret = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&pFactory);
		if(FAILED(ret))
		{
			return false;
		}

		ret = pFactory->CreateSwapChain(m_pDevice, &sd, &m_pSwapChain);

		if(FAILED(ret))
		{
			return false;
		}

		pFactory->Release();
		pDXGIAdapter->Release();
		pDXGIDevice->Release();


		// Create a render target view
		ID3D11Texture2D *pBackBuffer;

		if( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBackBuffer ) ) )
			return FALSE;

		ID3D11RenderTargetView* pRenderTargetView = NULL;
		ret = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &pRenderTargetView );
		pBackBuffer->Release();


		if( FAILED( ret ) )
			return FALSE;

		D3D11RenderTarget* pD3DRenderTarget = new D3D11RenderTarget;

		pD3DRenderTarget->Initialize(pRenderTargetView);

		m_pRenderTarget = RenderTargetPtr(pD3DRenderTarget);


		m_pDevice->GetImmediateContext(&m_pContext);


		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)param.width;
		vp.Height = (FLOAT)param.height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pContext->RSSetViewports( 1, &vp );

		return true;
	}
	void D3D11FrameBuffer::Release()
	{
		if(m_pRenderTarget != NULL)
		{
			m_pRenderTarget->Release();
			m_pRenderTarget.reset();
		}

		if(m_pSwapChain != NULL)
		{
			m_pSwapChain->Release();
			m_pSwapChain = NULL;
		}

		if(m_pContext != NULL)
		{
			m_pContext->Release();
			m_pContext = NULL;
		}

		m_pDevice = NULL;
	}
	
	void D3D11FrameBuffer::Present()
	{
		m_pSwapChain->Present(0, 0);
	}

	void D3D11FrameBuffer::ClearColor()
	{
		D3D11RenderTarget* pD3DRenderTarget = (D3D11RenderTarget* )(m_pRenderTarget.get());
		m_pContext->ClearRenderTargetView(pD3DRenderTarget->GetD3DRenderTargetView(), m_clearColor.v);
	}
	void D3D11FrameBuffer::ClearDepthStencil()
	{

	}
	void D3D11FrameBuffer::SetClearColor(const math::Color4& clr)
	{
		m_clearColor = clr;
	}
	void D3D11FrameBuffer::SetDepthStencil(float depth, uint32 stencil)
	{
		m_clearDepth = depth;
		m_clearStencil = stencil;
	}
	RenderTargetPtr	D3D11FrameBuffer::GetRenderTarget()
	{
		return m_pRenderTarget;
	}
}
