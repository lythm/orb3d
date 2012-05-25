#include "graphics_pch.h"
#include "D3D11Sys_Graphics.h"
#include "D3D11FrameBuffer.h"
#include "D3D11RenderTarget.h"
#include "D3D11GeometryBuffer.h"
#include "D3D11GraphicsFX.h"

namespace engine
{
	D3D11Sys_Graphics::D3D11Sys_Graphics(void)
	{
		m_pDevice					= NULL;

		m_pContext					= NULL;
	
	}


	D3D11Sys_Graphics::~D3D11Sys_Graphics(void)
	{
	}
	bool D3D11Sys_Graphics::Initialize(const GraphicsParameters& param)
	{
		HRESULT ret = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_SINGLETHREADED |  D3D11_CREATE_DEVICE_DEBUG, NULL, 0, D3D11_SDK_VERSION, &m_pDevice, NULL, &m_pContext);
		if( FAILED( ret ) )
		{
			return false;
		}

		D3D11FrameBuffer* pD3D11FrameBuffer = new D3D11FrameBuffer();

		if(false == pD3D11FrameBuffer->Initialize(m_pDevice, param))
		{
			return false;
		}
		
		
		m_pFrameBuffer = FrameBufferPtr(pD3D11FrameBuffer);

		SetRenderTarget(m_pFrameBuffer->GetRenderTarget());






		// test


		m_renderData.m_pGFX = CreateGFX();

		m_renderData.m_pGeometry = CreateGeometryBuffer();

		math::Vector3 vertex[3] = 
		{
			math::Vector3(0.0f, 0.5f, 0.5f ),
			math::Vector3(0.5f, -0.5f, 0.5f ),
			math::Vector3(-0.5f, -0.5f, 0.5f ),
		};

		m_renderData.m_pGeometry->AllocVertexBuffer(sizeof(math::Vector3) * 3, true);
		void* pBuffer = m_renderData.m_pGeometry->MapVertexBuffer(GeometryBuffer::MAP_DISCARD);

		memcpy(pBuffer, vertex, sizeof(math::Vector3) * 3);

		m_renderData.m_pGeometry->UnmapVertexBuffer();

		uint32 index[3] = 
		{
			0,1,2,
		};

		m_renderData.m_pGeometry->AllocIndexBuffer(sizeof(uint32) * 3, true);
		pBuffer = m_renderData.m_pGeometry->MapIndexBuffer(GeometryBuffer::MAP_DISCARD);

		memcpy(pBuffer, index, sizeof(uint32) * 3);
		m_renderData.m_pGeometry->UnmapIndexBuffer();
		

		m_renderData.m_primitive = RenderData::PRIMITIVE_TRIANGLELIST;
		return true;
	}
	void D3D11Sys_Graphics::Release()
	{

		


		m_renderData.m_pGeometry->FreeVertexBuffer();
		m_renderData.m_pGeometry->FreeIndexBuffer();
		m_renderData.m_pGFX->Release();




		m_pFrameBuffer->Release();


		m_pContext->Release();
		m_pContext = NULL;

		//int r = m_pDevice->AddRef();

		m_pDevice->Release();
		m_pDevice = NULL;

		
	}

	void D3D11Sys_Graphics::Render()
	{
		
		
		
	}
	void D3D11Sys_Graphics::SetClearColor(const math::Color4& clr)
	{
		m_pFrameBuffer->SetClearColor(clr);
	}
	void D3D11Sys_Graphics::SetClearDepth(float d)
	{
		m_pFrameBuffer->SetDepthStencil(d, 0);
	}
	void D3D11Sys_Graphics::Render(const RenderData& data)
	{
		m_renderData.m_pGeometry->Apply(sizeof(math::Vector3));

		switch(m_renderData.m_primitive)
		{
		case RenderData::PRIMITIVE_TRIANGLELIST:
			m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;
		default:
			break;
		}

		uint32 pass = 0;
		m_renderData.m_pGFX->Begin(pass);

		for(uint32 i = 0; i < pass; ++i)
		{
			m_renderData.m_pGFX->ApplyPass(i);
			m_pContext->DrawIndexed(3, 0, 0);
		}
		m_renderData.m_pGFX->End();
				
	}
	void D3D11Sys_Graphics::Present()
	{
		Render(m_renderData);

		
		m_pFrameBuffer->Present();
	}
	void D3D11Sys_Graphics::ClearRenderTarget()
	{
		m_pFrameBuffer->ClearColor();
	}
	void D3D11Sys_Graphics::PushRenderData(RenderDataPtr pData)
	{
	}
	void D3D11Sys_Graphics::SetRenderTarget(RenderTargetPtr pTarget)
	{
		D3D11RenderTarget* pD3DRenderTarget = (D3D11RenderTarget* )(pTarget.get());

		ID3D11RenderTargetView*	pView = pD3DRenderTarget->GetD3DRenderTargetView();

		m_pContext->OMSetRenderTargets(1, &pView, NULL);
		
	}
	GeometryBufferPtr D3D11Sys_Graphics::CreateGeometryBuffer()
	{

		return GeometryBufferPtr(new D3D11GeometryBuffer(m_pContext));
	}
	GraphicsFXPtr D3D11Sys_Graphics::CreateGFX()
	{
		return GraphicsFXPtr(new D3D11GraphicsFX(m_pContext));
	}
	FrameBufferPtr D3D11Sys_Graphics::GetFrameBuffer()
	{
		return m_pFrameBuffer;
	}
}
