#include "d11graphics_pch.h"

#include "D3D11Graphics.h"
#include "D3D11Buffer.h"
#include "D3D11cgGFX.h"

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
		m_clearColor					= math::Color4(0.1f, 0.2f, 0.3f, 1.0f);
		m_clearDepth					= 1.0f;
		m_clearStencil					= 0;

		//m_pCG							= NULL;
		m_pDevice						= NULL;
		m_pContext						= NULL;
		m_pSwapChain					= NULL;
		m_pFrameBuffer					= NULL;
		m_pDepthStencilBuffer			= NULL;
	}


	D3D11Graphics::~D3D11Graphics(void)
	{
	}
	bool D3D11Graphics::Initialize(void* app_handle, uint32 width, uint32 height)
	{
		
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

		sd.BufferCount										= 1;
		sd.BufferDesc.Width									= width;
		sd.BufferDesc.Height								= height;
		sd.BufferDesc.Format								= DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator					= 60;
		sd.BufferDesc.RefreshRate.Denominator				= 1;
		sd.BufferUsage										= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow										= (HWND)app_handle;
		sd.SampleDesc.Count									= 1;
		sd.SampleDesc.Quality								= 0;
		sd.Windowed											= TRUE;
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
		descDepth.Width = width;
		descDepth.Height = height;
        descDepth.MipLevels = 1;
        descDepth.ArraySize = 1;
        descDepth.Format = DXGI_FORMAT_D32_FLOAT;
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
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pContext->RSSetViewports( 1, &vp );


		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(math::Matrix44) * 3;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;


		math::Matrix44 mat[3];
		mat[0].MakeIdentity();
		mat[1].MakeIdentity();
		mat[2].MakeIdentity();


		D3D11_SUBRESOURCE_DATA InitData = {&mat, 0, 0,};
		
		ret = m_pDevice->CreateBuffer(&desc, &InitData, &m_pCB);
		if(FAILED(ret))
		{
			return false;
		}
		
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
	void D3D11Graphics::Release()
	{
		if(m_pCB)
		{
			m_pCB->Release();
			m_pCB = NULL;
		}

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

		cgD3D11RegisterStates( NULL);
		
		cgD3D11SetDevice(m_pCG, NULL);

		// cgD3D11SetDevice(m_pCG, NULL) does not release device reference , a bug?
		if(m_pDevice)
		{
			m_pDevice->Release();
		}	

		//


		cgDestroyContext(m_pCG);
		m_pCG = NULL;
		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}

	}


	void D3D11Graphics::Draw(RenderDataPtr pData)
	{
	}
	void D3D11Graphics::Render()
	{
		/*for(uint32 i = 0; i < m_queue.GetLength(); ++i)
		{
			RenderDataPtr pData = m_queue.GetAt(i);
			Draw(pData);
		}*/
	}

	//RenderDataPtr D3D11Graphics::CreateRenderData()
	//{
	//	return RenderDataPtr();
	//	//return RenderDataPtr(new D3D11RenderData(m_pContext));
	//}
	/*Texture2DPtr D3D11Graphics::CreateTexture2D()
	{
		return Texture2DPtr();
	}*/

	/*TexturePtr D3D11Graphics::CreateRenderTarget()
	{
		return TexturePtr();
	}*/
	void D3D11Graphics::SetViewTransform(const math::Matrix44& view)
	{
	}
	void D3D11Graphics::SetProjTransform(const math::Matrix44& proj)
	{
	}
	void D3D11Graphics::SetClearColor(const math::Color4& clr)
	{
		m_clearColor		= clr;
		
	}
	void D3D11Graphics::SetClearDepth(float d)
	{
		m_clearDepth		= d;
		
	}
	void D3D11Graphics::SetClearStencil(uint32 val)
	{
		m_clearStencil		= val;;
	}
	void D3D11Graphics::ClearRenderTarget()
	{
		m_pContext->ClearRenderTargetView(m_pFrameBuffer, m_clearColor.v);
		m_pContext->ClearDepthStencilView(m_pDepthStencilBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , m_clearDepth, m_clearStencil);
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
		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);

		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};

		if(FAILED(pDevice->CreateBuffer(&bufferDesc, pInitData == NULL ? NULL :&InitData, &pBuffer)))
		{
			pDevice->Release();
			return GPUBufferPtr();
		}
		pDevice->Release();


		return GPUBufferPtr(new D3D11Buffer(pBuffer, m_pContext));
	}

	GPUBufferPtr D3D11Graphics::CreateVertexBuffer(int bytes, void* pInitData, bool dynamic)
	{
		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = bytes;
		desc.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 12;
		desc.Usage = dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;


		ID3D11Buffer* pBuffer = NULL;
		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);


		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};
		
		HRESULT ret = pDevice->CreateBuffer(&desc, pInitData == NULL ? NULL : &InitData, &pBuffer);
		if(FAILED(ret))
		{
			pDevice->Release();
			return GPUBufferPtr();
		}

		pDevice->Release();
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
		ID3D11Device* pDevice = NULL;
		m_pContext->GetDevice(&pDevice);


		D3D11_SUBRESOURCE_DATA InitData = {pInitData, 0, 0,};
		
		HRESULT ret = pDevice->CreateBuffer(&desc, pInitData == NULL ? NULL : &InitData, &pBuffer);
		if(FAILED(ret))
		{
			pDevice->Release();
			return GPUBufferPtr();
		}

		pDevice->Release();
		return GPUBufferPtr(new D3D11Buffer(pBuffer, m_pContext));
	}
	void D3D11Graphics::SetIndexBuffer(GPUBufferPtr pBuffer)
	{
		ID3D11Buffer* pD3DBuffer = boost::shared_dynamic_cast<D3D11Buffer>(pBuffer)->GetD3D11BufferInterface();

		m_pContext->IASetIndexBuffer(pD3DBuffer, DXGI_FORMAT_R16_UINT, 0);
	}
	void D3D11Graphics::SetVertexBuffer(GPUBufferPtr pBuffer)
	{
		ID3D11Buffer* pD3DBuffer = boost::shared_dynamic_cast<D3D11Buffer>(pBuffer)->GetD3D11BufferInterface();

		UINT offset = 0;
		UINT stride = 0;//sizeof(math::Vector3);

		m_pContext->IASetVertexBuffers(0, 1, &pD3DBuffer, &stride, &offset);
	}
	/*void D3D11Graphics::SetRenderTarget(Texture2DPtr pTarget)
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

	ShaderPtr D3D11Graphics::CreateShader()
	{
		return ShaderPtr(new CGFXShader(m_pCG));
	}*/

	GFXPtr D3D11Graphics::CreateGFXFromFile(const char* szFile)
	{
		D3D11cgGFX* pFX = new D3D11cgGFX(m_pCG, m_pContext);

		if(false == pFX->LoadFromFile(szFile))
		{
			pFX->Release();
			return GFXPtr();
		}

		return GFXPtr(pFX);
	}
	void D3D11Graphics::DrawPrimitive(int count, int startindex, int basevertex)
	{
		m_pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pContext->DrawIndexed(count, startindex, basevertex);
	}
}
