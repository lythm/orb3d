#include "d11graphics_pch.h"

#include "D3D11Graphics.h"
#include "D3D11Buffer.h"
#include "D3D11Texture.h"
#include "D3D11EffectGFX.h"
#include "D3D11RenderTarget.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Format.h"
#include "D3D11MultiRenderTarget.h"

EXPORT_C_API engine::Sys_Graphics* CreateSys()
{
	return new engine::D3D11Graphics;
}

EXPORT_C_API void DestroySys(engine::Sys_Graphics* pSys)
{
	delete (engine::D3D11Graphics*)pSys;
}


namespace engine
{
	D3D11Graphics::D3D11Graphics(void)
	{
		m_pDevice						= NULL;
		m_pContext						= NULL;
		m_pSwapChain					= NULL;
		m_pFrameBuffer					= NULL;
		m_pDepthStencilBuffer			= NULL;
	}


	D3D11Graphics::~D3D11Graphics(void)
	{
	}
	bool D3D11Graphics::Initialize(const GraphicsSetting& setting)
	{
		m_setting = setting;

		//D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;

		D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_10_0;

		HRESULT ret = D3D11CreateDevice(NULL, 
			D3D_DRIVER_TYPE_HARDWARE /*D3D_DRIVER_TYPE_REFERENCE*/, 
			NULL, 
			D3D11_CREATE_DEVICE_SINGLETHREADED |  D3D11_CREATE_DEVICE_DEBUG, 
			&fl, 
			1, 
			D3D11_SDK_VERSION, 
			&m_pDevice, 
			NULL, 
			&m_pContext);
		if( FAILED( ret ) )
		{
			return false;
		}


		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof(sd) );

		sd.BufferCount										= m_setting.backBufferCount;
		sd.BufferDesc.Width									= m_setting.frameBufferWidth;
		sd.BufferDesc.Height								= m_setting.frameBufferHeight;
		sd.BufferDesc.Format								= D3D11Format::Convert(m_setting.frameBufferFormat);
		sd.BufferDesc.RefreshRate.Numerator					= 60;
		sd.BufferDesc.RefreshRate.Denominator				= 1;
		sd.BufferUsage										= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow										= (HWND)m_setting.wnd;
		sd.SampleDesc.Count									= m_setting.multiSampleCount;
		sd.SampleDesc.Quality								= m_setting.multiSampleQuality;
		sd.Windowed											= m_setting.windowed;
		sd.SwapEffect										= DXGI_SWAP_EFFECT_DISCARD;
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


		if(CreateFrameBuffer() == false)
		{
			return false;
		}
		if(CreateDepthStencilBuffer(setting) == false)
		{
			return false;
		}

		m_pContext->OMSetRenderTargets(1, &m_pFrameBuffer, m_pDepthStencilBuffer);
		m_pContext->OMSetBlendState(NULL, 0, -1);

		SetupViewport(m_setting.frameBufferWidth , m_setting.frameBufferHeight);
		
		return true;
	}
	void D3D11Graphics::SetupViewport(int w, int h)
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

	bool D3D11Graphics::CreateFrameBuffer()
	{
		// Create a render target view
		ID3D11Texture2D *pBackBuffer;

		if( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBackBuffer ) ) )
			return false;

		HRESULT ret = m_pDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pFrameBuffer);
		pBackBuffer->Release();

		if( FAILED( ret ) )
			return false;

		return true;
	}
	bool D3D11Graphics::CreateDepthStencilBuffer(const GraphicsSetting& setting)
	{
		// Create depth stencil texture
		ID3D11Texture2D* pDepthStencil = NULL;
		D3D11_TEXTURE2D_DESC descDepth;

		ZeroMemory(&descDepth, sizeof(descDepth));

		descDepth.Width = setting.frameBufferWidth;
		descDepth.Height = setting.frameBufferHeight;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = D3D11Format::Convert(setting.depthStencilFormat);
		descDepth.SampleDesc.Count = setting.multiSampleCount;
		descDepth.SampleDesc.Quality = setting.multiSampleQuality;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		HRESULT ret = m_pDevice->CreateTexture2D( &descDepth, NULL, &pDepthStencil );
		if( FAILED( ret ) )
			return false;

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
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

		pDepthStencil->Release();

		return true;
	}
	void D3D11Graphics::Release()
	{
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


		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}

	}

	void D3D11Graphics::ClearRenderTarget(RenderTargetPtr pTarget, const math::Color4& clr, float d, int s, CLEAR_RENDERTARGET_FLAG flag)
	{
		ID3D11RenderTargetView* pRTView = NULL;
		ID3D11DepthStencilView* pDV = NULL;
		if(pTarget != nullptr)
		{
			pRTView = ((D3D11RenderTarget*)pTarget.get())->GetD3D11RenderTargetView();
			pDV = ((D3D11RenderTarget*)pTarget.get())->GetD3D11DepthStencilView();
		}

		if(flag & CLEAR_COLOR_BUFFER)
		{
			m_pContext->ClearRenderTargetView(pRTView == NULL ? m_pFrameBuffer : pRTView, clr.v);
		}

		if(flag & CLEAR_DEPTHSTENCIL_BUFFER)
		{
			m_pContext->ClearDepthStencilView(pDV == NULL ? m_pDepthStencilBuffer : pDV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , d, s);
		}
	}
	void D3D11Graphics::Present()
	{
		m_pSwapChain->Present(0, 0);
	}

	GPUBufferPtr D3D11Graphics::CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic)
	{
		GPUBufferPtr pBuffer;

		switch(type)
		{
		case BT_VERTEX_BUFFER:
			pBuffer = CreateVertexBuffer(bytes, pInitData, dynamic);
			break;
		case BT_INDEX_BUFFER:
			pBuffer = CreateIndexBuffer(bytes, pInitData, dynamic);
			break;
		case BT_CONSTANT_BUFFER:
			pBuffer = CreateConstantBuffer(bytes, pInitData);
			break;
		default:
			return GPUBufferPtr();
		}

		return pBuffer;

	}
	GPUBufferPtr D3D11Graphics::CreateIndexBuffer(int bytes, void* pInitData, bool dynamic)
	{
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage           = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth       = bytes;
		bufferDesc.BindFlags       = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags  = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		bufferDesc.MiscFlags       = 0;
		bufferDesc.StructureByteStride = 0;

		ID3D11Buffer* pBuffer = NULL;

		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};

		if(FAILED(m_pDevice->CreateBuffer(&bufferDesc, pInitData == NULL ? NULL :&InitData, &pBuffer)))
		{
			return GPUBufferPtr();
		}

		return GPUBufferPtr(new D3D11Buffer(pBuffer, m_pContext));
	}

	GPUBufferPtr D3D11Graphics::CreateVertexBuffer(int bytes, void* pInitData, bool dynamic)
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = bytes;
		desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;


		ID3D11Buffer* pBuffer = NULL;

		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};

		HRESULT ret = m_pDevice->CreateBuffer(&desc, pInitData == NULL ? NULL : &InitData, &pBuffer);
		if(FAILED(ret))
		{
			return GPUBufferPtr();
		}

		return GPUBufferPtr(new D3D11Buffer(pBuffer, m_pContext));
	}

	GPUBufferPtr D3D11Graphics::CreateConstantBuffer(int bytes, void* pInitData)
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = bytes;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;


		ID3D11Buffer* pBuffer = NULL;

		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};

		HRESULT ret = m_pDevice->CreateBuffer(&desc, pInitData == NULL ? NULL : &InitData, &pBuffer);
		if(FAILED(ret))
		{
			return GPUBufferPtr();
		}

		return GPUBufferPtr(new D3D11Buffer(pBuffer, m_pContext));
	}
	void D3D11Graphics::SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type)
	{
		ID3D11Buffer* pD3DBuffer = boost::shared_dynamic_cast<D3D11Buffer>(pBuffer)->GetD3D11BufferInterface();
		
		m_pContext->IASetIndexBuffer(pD3DBuffer, D3D11Format::Convert(type), 0);
	}
	void D3D11Graphics::SetVertexBuffer(GPUBufferPtr pBuffer, unsigned int offset, unsigned int stride)
	{
		ID3D11Buffer* pD3DBuffer = boost::shared_dynamic_cast<D3D11Buffer>(pBuffer)->GetD3D11BufferInterface();

		m_pContext->IASetVertexBuffers(0, 1, &pD3DBuffer, &stride, &offset);
	}
	void D3D11Graphics::SetRenderTarget(RenderTargetPtr pRenderTarget)
	{
		D3D11RenderTarget* pD3DRT = (D3D11RenderTarget*)pRenderTarget.get();
				
		ID3D11RenderTargetView* pRTView = NULL;
		ID3D11DepthStencilView* pDSView = NULL;

		if(pD3DRT)
		{
			pRTView = pD3DRT->GetD3D11RenderTargetView();
			pDSView = pD3DRT->GetD3D11DepthStencilView();
		}
				
		ID3D11ShaderResourceView* pViews[8] = { NULL,};

		m_pContext->PSSetShaderResources(0, 8, pViews);

		m_pContext->OMSetRenderTargets(1, 
					pRTView == NULL ? &m_pFrameBuffer : &pRTView, 
					pDSView == NULL ? m_pDepthStencilBuffer : pDSView);

	}
	
	GFXPtr D3D11Graphics::CreateGFXFromFile(const char* szFile)
	{
		D3D11EffectGFX* pFX = new D3D11EffectGFX(m_pContext);

		if(false == pFX->LoadFromFile(szFile))
		{
			pFX->Release();
			return GFXPtr();
		}

		return GFXPtr(pFX);
	}
	void D3D11Graphics::SetPrimitiveType(PRIMITIVE_TYPE pt)
	{
		D3D_PRIMITIVE_TOPOLOGY tp = D3D11Format::Convert(pt);
		m_pContext->IASetPrimitiveTopology(tp);
	}
	void D3D11Graphics::DrawPrimitive(int count, int startindex, int basevertex)
	{
		m_pContext->DrawIndexed(count, startindex, basevertex);
	}

	TexturePtr D3D11Graphics::CreateTextureFromFile(const char* szFile)
	{

		D3D11Texture* pTex = new D3D11Texture(m_pContext);

		if(pTex->LoadFromFile(szFile) == false)
		{
			delete pTex;
			return TexturePtr();
		}

		return TexturePtr(pTex);
	}

	RenderTargetPtr D3D11Graphics::CreateRenderTarget(int w, int h, G_FORMAT format, int miplvls)
	{
		D3D11RenderTarget* pTarget = new D3D11RenderTarget(m_pContext);

		if(pTarget->Create(w, h , format, miplvls) == false)
		{
			delete pTarget;
			return RenderTargetPtr();
		}

		return RenderTargetPtr(pTarget);
	}
	DepthStencilBufferPtr D3D11Graphics::CreateDepthStencilBuffer(int w, int h, G_FORMAT format)
	{
		D3D11DepthStencilBuffer* pTarget = new D3D11DepthStencilBuffer(m_pContext);

		if(false == pTarget->Create(w, h, format))
		{
			delete pTarget;
			return DepthStencilBufferPtr();
		}
		
		return DepthStencilBufferPtr(pTarget);
	}
	void D3D11Graphics::SetRenderTarget(MultiRenderTargetPtr pRT)
	{
		if(pRT == nullptr)
		{
			SetRenderTarget(RenderTargetPtr());
			return;
		}

		D3D11MultiRenderTarget* pD3DRT = (D3D11MultiRenderTarget*)pRT.get();
				
		ID3D11RenderTargetView** pRTViews = pD3DRT->GetD3D11RenderTargetViews();
		ID3D11DepthStencilView* pDSView = pD3DRT->GetD3D11DepthStencilView();

		ID3D11ShaderResourceView* pViews[8] = { NULL,};
		m_pContext->PSSetShaderResources(0, 8, pViews);

		m_pContext->OMSetRenderTargets(pRT->GetRenderTargetCount(), 
					pRTViews, 
					pDSView == NULL ? m_pDepthStencilBuffer : pDSView);
	}

	TexturePtr D3D11Graphics::CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h)
	{
		return TexturePtr();
	}
	void D3D11Graphics::ResizeFrameBuffer(int cx, int cy)
	{
		if(m_pFrameBuffer != NULL)
		{
			m_pFrameBuffer->Release();
			m_pFrameBuffer = NULL;
		}

		
		if(m_pDepthStencilBuffer)
		{
			m_pDepthStencilBuffer->Release();
			m_pDepthStencilBuffer = NULL;
		}
		m_setting.frameBufferWidth = cx;
		m_setting.frameBufferHeight = cy;

		m_pSwapChain->ResizeBuffers(2, cx, cy, D3D11Format::Convert(m_setting.frameBufferFormat), 0);

		CreateFrameBuffer();
		CreateDepthStencilBuffer(m_setting);
		SetupViewport(cx, cy);

	}
	MultiRenderTargetPtr D3D11Graphics::CreateMultiRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls)
	{
		D3D11MultiRenderTarget* pTarget = new D3D11MultiRenderTarget(m_pContext);
		if(pTarget->Create(count, w, h, formats, miplvls) == false)
		{
			delete pTarget;
			return MultiRenderTargetPtr();
		}

		return MultiRenderTargetPtr(pTarget);
	}
}

