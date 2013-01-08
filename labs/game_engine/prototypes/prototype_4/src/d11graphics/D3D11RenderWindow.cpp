#include "d11graphics_pch.h"
#include "D3D11RenderWindow.h"

#include "D3D11Texture.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Format.h"

namespace engine
{
	D3D11RenderWindow::D3D11RenderWindow(ID3D11DeviceContext* pContext)
	{
		m_pContext					= pContext;

		m_pDevice					= NULL;

		m_pContext->GetDevice(&m_pDevice);
		m_pRenderTargetView			= NULL;

	}


	D3D11RenderWindow::~D3D11RenderWindow(void)
	{
	}
	bool D3D11RenderWindow::Create(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed)
	{

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof(sd) );

		sd.BufferCount										= backbufferCount;
		sd.BufferDesc.Width									= w;
		sd.BufferDesc.Height								= h;
		sd.BufferDesc.Format								= D3D11Format::Convert(color_format);
		sd.BufferDesc.RefreshRate.Numerator					= 60;
		sd.BufferDesc.RefreshRate.Denominator				= 1;
		sd.BufferUsage										= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow										= (HWND)handle;
		sd.SampleDesc.Count									= multiSampleCount;
		sd.SampleDesc.Quality								= multiSampleQuality;
		sd.Windowed											= windowed;
		sd.SwapEffect										= DXGI_SWAP_EFFECT_DISCARD;
		//sd.Flags											= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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


		if(CreateFrameBuffer() == false)
		{
			return false;
		}

		D3D11DepthStencilBuffer* pTarget = new D3D11DepthStencilBuffer(m_pContext);

		if(false == pTarget->Create(w, h, ds_format))
		{
			delete pTarget;
			return false;
		}
		
		m_pDepthBuffer = DepthStencilBufferPtr(pTarget);


		m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, pTarget->GetD3D11DepthStencilView());
		m_pContext->OMSetBlendState(NULL, 0, -1);

		SetupViewport(w, h);

		return true;
	}
	
	void D3D11RenderWindow::Release()
	{
		if(m_pRenderTargetView != NULL)
		{
			m_pRenderTargetView->Release();
			m_pRenderTargetView = NULL;
		}

		if(m_pContext)
		{
			m_pContext->Release();
			m_pContext = NULL;
		}


		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}

		if(m_pSwapChain != NULL)
		{
			m_pSwapChain->Release();
			m_pSwapChain = NULL;
		}

		m_pDepthBuffer->Release();

		m_pDepthBuffer.reset();

		m_pContext = NULL;
	}
	
	ID3D11RenderTargetView*	D3D11RenderWindow::GetD3D11RenderTargetView()
	{
		return m_pRenderTargetView;
	}
	ID3D11DepthStencilView*	D3D11RenderWindow::GetD3D11DepthStencilView()
	{
		if(m_pDepthBuffer == nullptr)
		{
			return nullptr;
		}
		return ((D3D11DepthStencilBuffer*)m_pDepthBuffer.get())->GetD3D11DepthStencilView();
	}
	TexturePtr D3D11RenderWindow::AsTexture()
	{
		return TexturePtr();
	}

	DepthStencilBufferPtr D3D11RenderWindow::GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}
	void D3D11RenderWindow::SetDepthStencilBuffer(DepthStencilBufferPtr pBuffer)
	{
		m_pDepthBuffer = pBuffer;
	}
	bool D3D11RenderWindow::CreateFrameBuffer()
	{
		// Create a render target view
		ID3D11Texture2D *pBackBuffer;

		if( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBackBuffer ) ) )
			return false;

		HRESULT ret = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();

		if( FAILED( ret ) )
			return false;

		return true;
	}
	void D3D11RenderWindow::SetupViewport(int w, int h)
	{
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)w;
		vp.Height = (FLOAT)h;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pContext->RSSetViewports( 1, &vp );
	}
	
}
