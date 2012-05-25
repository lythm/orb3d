#include "graphics_pch.h"
#include "D3D11SysGraphics.h"
#include "types\dllexport.h"

#include "D3D11Texture2D.h"
#include "D3D11RenderData.h"
#include "GFXShader.h"


EXPORT_C_API engine::SysGraphics* CreateSys()
{
	return new engine::D3D11SysGraphics;
}

EXPORT_C_API void DestroySys(engine::SysGraphics* pSys)
{
	delete (engine::D3D11SysGraphics*)pSys;
}




namespace engine
{
	D3D11SysGraphics::D3D11SysGraphics(void)
	{
		m_clearColor					= math::Color4(0.1f, 0.2f, 0.3f, 1.0f);
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;

		m_pCG							= NULL;
		m_pDevice						= NULL;
		m_pContext						= NULL;
		m_pSwapChain					= NULL;
		m_pFrameBuffer					= NULL;
		m_pDepthStencilBuffer			= NULL;

		
	}


	D3D11SysGraphics::~D3D11SysGraphics(void)
	{
	}


	void D3D11SysGraphics::ClearRenderQueue()
	{
		m_queue.Clear();
	}
	void D3D11SysGraphics::Draw(RenderDataPtr pData)
	{
	}
	void D3D11SysGraphics::PushRenderData(RenderDataPtr pData)
	{
		m_queue.Push(pData);
	}
	void D3D11SysGraphics::Render()
	{
		for(uint32 i = 0; i < m_queue.GetLength(); ++i)
		{
			RenderDataPtr pData = m_queue.GetAt(i);
			Draw(pData);
		}
	}

	RenderDataPtr D3D11SysGraphics::CreateRenderData()
	{

		return RenderDataPtr(new D3D11RenderData(m_pContext));
	}
	Texture2DPtr D3D11SysGraphics::CreateTexture2D()
	{
		return Texture2DPtr();
	}

	TexturePtr D3D11SysGraphics::CreateRenderTarget()
	{
		return TexturePtr();
	}
	bool D3D11SysGraphics::Initialize(const SysGraphicsParameters& param)
	{
		HRESULT ret = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE /*D3D_DRIVER_TYPE_REFERENCE*/, NULL, D3D11_CREATE_DEVICE_SINGLETHREADED |  D3D11_CREATE_DEVICE_DEBUG, NULL, 0, D3D11_SDK_VERSION, &m_pDevice, NULL, &m_pContext);
		if( FAILED( ret ) )
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
		sd.OutputWindow										= (HWND)param.app_handle;
		sd.SampleDesc.Count									= 1;
		sd.SampleDesc.Quality								= 0;
		sd.Windowed											= TRUE;
		sd.SwapEffect										= DXGI_SWAP_EFFECT_SEQUENTIAL;
		//sd.Flags											= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGIFactory1* pFactory = NULL;

		IDXGIDevice* pDXGIDevice = NULL;

		ret = m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
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

		ret = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pFrameBuffer);
		pBackBuffer->Release();


		if( FAILED( ret ) )
			return FALSE;

		// Create depth stencil texture
        ID3D11Texture2D* pDepthStencil = NULL;
        D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = param.width;
		descDepth.Height = param.height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        descDepth.SampleDesc.Count = 1;
        descDepth.SampleDesc.Quality = 0;
        descDepth.Usage = D3D11_USAGE_DEFAULT;
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        descDepth.CPUAccessFlags = 0;
        descDepth.MiscFlags = 0;
        ret = m_pDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil );
        if( FAILED( ret ) )
            return false;

        // Create the depth stencil view
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        descDSV.Format = descDepth.Format;
        descDSV.Flags = 0;
        if( descDepth.SampleDesc.Count > 1 )
            descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        else
            descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        descDSV.Texture2D.MipSlice = 0;
        ret = m_pDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &m_pDepthStencilBuffer );
        if( FAILED( ret ) )
            return false;
        
		m_pContext->OMSetRenderTargets(1, &m_pFrameBuffer, m_pDepthStencilBuffer);

		pDepthStencil->Release();

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)param.width;
		vp.Height = (FLOAT)param.height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pContext->RSSetViewports( 1, &vp );




		HRESULT hr = S_OK;

		m_pCG = cgCreateContext();
		if(m_pCG == NULL)
		{
			return false;
		}

		hr = cgD3D11SetDevice( m_pCG, m_pDevice);
		if( hr != S_OK )
		{
			return false;
		}

		cgD3D11RegisterStates( m_pCG);
			
		cgD3D11SetManageTextureParameters( m_pCG, CG_TRUE );
		
		return true;
	}
	void D3D11SysGraphics::Release()
	{
		m_queue.Clear();

		if(m_pDepthStencilBuffer)
		{
			m_pDepthStencilBuffer->Release();
			m_pDepthStencilBuffer = NULL;
		}

		if(m_pFrameBuffer != NULL)
		{
			m_pFrameBuffer->Release();
			m_pFrameBuffer = NULL;
		}

		if(m_pSwapChain != NULL)
		{
			m_pSwapChain->Release();
			m_pSwapChain = NULL;
		}

		if(m_pContext)
		{
			m_pContext->Release();
			m_pContext = NULL;
		}

		cgD3D11SetDevice(m_pCG, NULL);
		if(m_pDevice)
		{
			m_pDevice->Release();
		}

		cgD3D11RegisterStates( NULL);
		cgDestroyContext(m_pCG);

		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}

	}

	void D3D11SysGraphics::SetViewTransform(const math::Matrix44& view)
	{
	}
	void D3D11SysGraphics::SetProjTransform(const math::Matrix44& proj)
	{
	}
	void D3D11SysGraphics::SetClearColor(const math::Color4& clr)
	{
		m_clearColor		= clr;
		
	}
	void D3D11SysGraphics::SetClearDepth(float d)
	{
		m_clearDepth		= d;
		
	}
	void D3D11SysGraphics::SetClearStencil(uint32 val)
	{
		m_clearStencil		= val;;
	}
	void D3D11SysGraphics::ClearRenderTarget()
	{
		m_pContext->ClearRenderTargetView(m_pFrameBuffer, m_clearColor.v);
		m_pContext->ClearDepthStencilView(m_pDepthStencilBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , m_clearDepth, m_clearStencil);
	}
	void D3D11SysGraphics::Present()
	{
		m_pSwapChain->Present(0, 0);
	}
	void D3D11SysGraphics::SetRenderTarget(Texture2DPtr pTarget)
	{
		if(pTarget == NULL)
		{
			m_pContext->OMSetRenderTargets(1, &m_pFrameBuffer, m_pDepthStencilBuffer);
			return;
		}

		D3D11Texture2D* pTex = (D3D11Texture2D*)pTarget.get();

		ID3D11RenderTargetView* pView = pTex->GetD3D11RenderTargetView();

		if(pView == NULL)
		{
			m_pContext->OMSetRenderTargets(1, &m_pFrameBuffer, m_pDepthStencilBuffer);
			return;
		}

		m_pContext->OMSetRenderTargets(1, &pView, m_pDepthStencilBuffer);
	}

	ShaderPtr D3D11SysGraphics::CreateShader()
	{
		return ShaderPtr(new CGFXShader(m_pCG));
	}
}
