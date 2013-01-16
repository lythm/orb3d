#include "d11graphics_pch.h"
#include "D3D11RenderWindow.h"

#include "D3D11Texture.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Format.h"

namespace ld3d
{
	D3D11RenderWindow::D3D11RenderWindow(ID3D11DeviceContext* pContext) : D3D11RenderTarget(pContext)
	{
		m_pSwapChain				= NULL;

		m_frameBufferFormat			= G_FORMAT_UNKNOWN;
		m_dsFormat					= G_FORMAT_UNKNOWN;
		m_backbufferCount			= 0;
		m_multiSampleCount			= 0;
		m_multiSampleQuality		= 0;

	}


	D3D11RenderWindow::~D3D11RenderWindow(void)
	{
	}
	bool D3D11RenderWindow::Create(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed)
	{

		m_width						= w;
		m_height					= h;
		m_frameBufferFormat			= color_format;
		m_dsFormat					= ds_format;
		m_backbufferCount			= backbufferCount;
		m_multiSampleCount			= multiSampleCount;
		m_multiSampleQuality		= multiSampleQuality;

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

		m_pRTViews = new ID3D11RenderTargetView*[1];

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

		return true;
	}
	
	void D3D11RenderWindow::Release()
	{
		if(m_pSwapChain != NULL)
		{
			m_pSwapChain->Release();
			m_pSwapChain = NULL;
		}
		m_pRTViews[0]->Release();

		m_pDepthBuffer->Release();
		m_pDepthBuffer.reset();
		m_pContext = NULL;

		D3D11RenderTarget::Release();
	}
	
	TexturePtr D3D11RenderWindow::AsTexture(int index)
	{
		return TexturePtr();
	}

	bool D3D11RenderWindow::CreateFrameBuffer()
	{
		// Create a render target view
		ID3D11Texture2D *pBackBuffer;

		if( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBackBuffer ) ) )
			return false;

		HRESULT ret = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRTViews[0]);
		pBackBuffer->Release();

		if( FAILED( ret ) )
			return false;

		return true;
	}
	int	D3D11RenderWindow::GetRenderTargetCount()
	{
		return 1;
	}

	void D3D11RenderWindow::Present()
	{
		m_pSwapChain->Present(0, 0);
	}
	void D3D11RenderWindow::Resize(int cx, int cy)
	{
		if(m_pRTViews[0] != NULL)
		{
			m_pRTViews[0]->Release();
			m_pRTViews[0] = NULL;
		}

		
		if(m_pDepthBuffer)
		{
			m_pDepthBuffer->Release();
			m_pDepthBuffer.reset();
		}
		m_width		= cx;
		m_height	= cy;

		m_pSwapChain->ResizeBuffers(m_backbufferCount, cx, cy, D3D11Format::Convert(m_frameBufferFormat), 0);

		CreateFrameBuffer();

		D3D11DepthStencilBuffer* pTarget = new D3D11DepthStencilBuffer(m_pContext);

		if(false == pTarget->Create(m_width, m_height, m_dsFormat))
		{
			delete pTarget;
			return;
		}
		
		m_pDepthBuffer = DepthStencilBufferPtr(pTarget);

	}
}
