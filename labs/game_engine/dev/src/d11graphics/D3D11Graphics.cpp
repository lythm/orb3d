#include "d11graphics_pch.h"

#include "D3D11Graphics.h"
#include "D3D11Buffer.h"
#include "D3D11Texture.h"
#include "D3D11EffectMaterial.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Format.h"
#include "D3D11RenderTarget.h"
#include "D3D11RenderWindow.h"

EXPORT_C_API ld3d::Sys_Graphics* CreateSys()
{
	return new ld3d::D3D11Graphics;
}

EXPORT_C_API void DestroySys(ld3d::Sys_Graphics* pSys)
{
	delete (ld3d::D3D11Graphics*)pSys;
}

namespace ld3d
{
	D3D11Graphics::D3D11Graphics(void)
	{
		m_pDevice						= NULL;
		m_pContext						= NULL;

		ZeroMemory(&m_viewPort, sizeof(m_viewPort));
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


		if(false == CreateDefaultRenderTarget(setting))
		{
			return false;
		}

		SetRenderWindow(m_pDefaultRW);

		m_pContext->OMSetBlendState(NULL, 0, -1);

		SetViewPort(0, 0, m_setting.frameBufferWidth , m_setting.frameBufferHeight);
		
		return true;
	}
	void D3D11Graphics::SetViewPort(int x, int y, int w, int h)
	{
		m_viewPort.Width = (FLOAT)w;
		m_viewPort.Height = (FLOAT)h;
		m_viewPort.MinDepth = 0.0f;
		m_viewPort.MaxDepth = 1.0f;
		m_viewPort.TopLeftX = x;
		m_viewPort.TopLeftY = y;
		m_pContext->RSSetViewports( 1, &m_viewPort );
	}

	
	void D3D11Graphics::Release()
	{
		m_pCurrentRW.reset();

		if(m_pDefaultRW)
		{
			m_pDefaultRW->Release();
			m_pDefaultRW.reset();
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
	void D3D11Graphics::ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, CLEAR_DS_FLAG flag, float d, int s)
	{
		ID3D11DepthStencilView* pDV = NULL;
		if(pTarget != nullptr)
		{
			pDV = ((D3D11DepthStencilBuffer*)pTarget.get())->GetD3D11DepthStencilView();
		}
		int d3d11_clear = 0;
		if(flag & CLEAR_DEPTH)
		{
			d3d11_clear |= D3D11_CLEAR_DEPTH;
		}
		if(flag & CLEAR_STENCIL)
		{
			d3d11_clear |= D3D11_CLEAR_STENCIL;
		}
		m_pContext->ClearDepthStencilView(pDV == NULL ? m_pCurrentRW->GetD3D11DepthStencilView() : pDV, d3d11_clear, d, s);
	}
	
	void D3D11Graphics::ClearRenderTarget(RenderTargetPtr pTarget, int index, const math::Color4& clr)
	{
		ID3D11RenderTargetView* pRTView = NULL;
		if(pTarget != nullptr)
		{
			pRTView = ((D3D11RenderTarget*)pTarget.get())->GetD3D11RenderTargetView(index);
		}
		m_pContext->ClearRenderTargetView(pRTView == NULL ? m_pCurrentRW->GetD3D11RenderTargetView(index) : pRTView, clr.v);
	}
	void D3D11Graphics::Present()
	{
		m_pCurrentRW->Present();
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
	void D3D11Graphics::VSSetConstantBuffer(GPUBufferPtr pBuffer)
	{
		ID3D11Buffer* pCB = ((D3D11Buffer*)pBuffer.get())->GetD3D11BufferInterface(); 
		m_pContext->VSSetConstantBuffers(0, 1, &pCB);
	}
	void D3D11Graphics::PSSetConstantBuffer(GPUBufferPtr pBuffer)
	{
		ID3D11Buffer* pCB = ((D3D11Buffer*)pBuffer.get())->GetD3D11BufferInterface(); 
		m_pContext->PSSetConstantBuffers(0, 1, &pCB);
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
	
	MaterialPtr D3D11Graphics::CreateMaterialFromFile(const char* szFile)
	{
		D3D11EffectMaterial* pFX = new D3D11EffectMaterial(m_pContext);

		if(false == pFX->LoadFromFile(szFile))
		{
			pFX->Release();
			return MaterialPtr();
		}

		return MaterialPtr(pFX);
	}
	void D3D11Graphics::SetPrimitiveType(PRIMITIVE_TYPE pt)
	{
		D3D_PRIMITIVE_TOPOLOGY tp = D3D11Format::Convert(pt);
		m_pContext->IASetPrimitiveTopology(tp);
	}
	void D3D11Graphics::DrawIndexed(int count, int startindex, int basevertex)
	{
		m_pContext->DrawIndexed(count, startindex, basevertex);
	}
	void D3D11Graphics::Draw(int vertexCount, int baseVertex)
	{
		m_pContext->Draw(vertexCount, baseVertex);
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
	void D3D11Graphics::SetRenderTarget(RenderTargetPtr pRT)
	{
		if(pRT == nullptr)
		{
			SetRenderTarget(m_pCurrentRW);
			return;
		}

		D3D11RenderTarget* pD3DRT = (D3D11RenderTarget*)pRT.get();
				
		ID3D11RenderTargetView** pRTViews = pD3DRT->GetD3D11RenderTargetViews();
		ID3D11DepthStencilView* pDSView = pD3DRT->GetD3D11DepthStencilView();

		ID3D11ShaderResourceView* pViews[8] = { NULL,};
		m_pContext->PSSetShaderResources(0, 8, pViews);

		m_pContext->OMSetRenderTargets(pD3DRT->GetRenderTargetCount(), 
					pRTViews, 
					pDSView == NULL ? m_pCurrentRW->GetD3D11DepthStencilView() : pDSView);

	}
	void D3D11Graphics::SetRenderWindow(RenderTargetPtr pWnd)
	{
		if(pWnd == RenderTargetPtr())
		{
			m_pCurrentRW = m_pDefaultRW;
			SetRenderTarget(m_pCurrentRW);
			return;
		}
		m_pCurrentRW = boost::shared_dynamic_cast<D3D11RenderWindow>(pWnd);

		SetRenderTarget(m_pCurrentRW);
	}

	TexturePtr D3D11Graphics::CreateTexture(TEXTURE_TYPE type, G_FORMAT format, int w, int h)
	{
		return TexturePtr();
	}
	void D3D11Graphics::ResizeFrameBuffer(int cx, int cy)
	{
		m_pCurrentRW->Resize(cx, cy);
		m_setting.frameBufferWidth = cx;
		m_setting.frameBufferHeight = cy;

		//SetViewPort(0, 0, cx, cy);
	}
	RenderTargetPtr D3D11Graphics::CreateRenderTarget(int count, int w, int h, G_FORMAT formats[], int miplvls)
	{
		D3D11RenderTarget* pTarget = new D3D11RenderTarget(m_pContext);
		if(pTarget->Create(count, w, h, formats, miplvls) == false)
		{
			delete pTarget;
			return RenderTargetPtr();
		}

		return RenderTargetPtr(pTarget);
	}
	const GraphicsSetting& D3D11Graphics::GetGraphicsSetting()
	{
		return m_setting;
	}
	ShaderPtr D3D11Graphics::CreateShaderFromFile(const char* szFile)
	{
		return ShaderPtr();
	}
	RenderStatePtr D3D11Graphics::CreateRenderState()
	{
		return RenderStatePtr();
	}
	RenderTargetPtr	D3D11Graphics::CreateRenderWindow(void* handle, int w, int h, G_FORMAT color_format, G_FORMAT ds_format, int backbufferCount, int multiSampleCount, int multiSampleQuality, bool windowed)
	{
		D3D11RenderWindow* pWnd = new D3D11RenderWindow(m_pContext);
		if(pWnd->Create(handle, w, h, color_format, ds_format, backbufferCount, multiSampleCount, multiSampleQuality, windowed) == false)
		{
			delete pWnd;
			return RenderTargetPtr();
		}
		return RenderTargetPtr(pWnd);
	}
	RenderTargetPtr D3D11Graphics::GetDefaultRenderTarget()
	{
		return m_pDefaultRW;
	}
	bool D3D11Graphics::CreateDefaultRenderTarget(const GraphicsSetting& setting)
	{
		m_pDefaultRW = boost::shared_dynamic_cast<D3D11RenderWindow>(CreateRenderWindow(setting.wnd, 
								setting.frameBufferWidth, 
								setting.frameBufferHeight,
								setting.frameBufferFormat,
								setting.depthStencilFormat,
								setting.backBufferCount,
								setting.multiSampleCount,
								setting.multiSampleQuality,
								setting.windowed));

		if(m_pDefaultRW == boost::shared_ptr<D3D11RenderWindow>())
		{
			return false;
		}
		
		return true;
	}

	int D3D11Graphics::GetFrameBufferWidth()
	{
		return m_pCurrentRW->GetWidth(0);
	}
	int D3D11Graphics::GetFrameBufferHeight()
	{
		return m_pCurrentRW->GetHeight(0);
	}
	RenderTargetPtr D3D11Graphics::GetCurrentRenderTarget()
	{
		return m_pCurrentRW;
	}
}

