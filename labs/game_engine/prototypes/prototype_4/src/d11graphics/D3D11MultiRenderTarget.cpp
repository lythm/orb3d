#include "d11graphics_pch.h"
#include "D3D11MultiRenderTarget.h"
#include "D3D11RenderTarget.h"
#include "D3D11DepthStencilBuffer.h"

namespace engine
{
	D3D11MultiRenderTarget::D3D11MultiRenderTarget(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;
		m_pRTViews = NULL;
	}


	D3D11MultiRenderTarget::~D3D11MultiRenderTarget(void)
	{
	}
		
	int D3D11MultiRenderTarget::GetRenderTargetCount()
	{
		return (int)m_RTs.size();
	}
	TexturePtr D3D11MultiRenderTarget::AsTexture(int index)
	{
		RenderTargetPtr pRT = m_RTs[index];
		return pRT->AsTexture();
	}
	void D3D11MultiRenderTarget::SetDepthStencilBuffer(DepthStencilBufferPtr pDepthBuffer)
	{
		m_pDepthBuffer = pDepthBuffer;
	}
	DepthStencilBufferPtr D3D11MultiRenderTarget::GetDepthStencilBuffer()
	{
		return m_pDepthBuffer;
	}
	void D3D11MultiRenderTarget::Release()
	{
		m_pContext = NULL;

		delete [] m_pRTViews;
		m_pRTViews = NULL;

		for(size_t i = 0; i < m_RTs.size(); ++i)
		{
			m_RTs[i]->Release();
		}
		m_RTs.clear();
	}
	bool D3D11MultiRenderTarget::Create(int count, int w, int h, G_FORMAT format, int miplvls)
	{
		if(count == 0)
		{
			return false;
		}
		m_pRTViews = new ID3D11RenderTargetView*[count];

		for(int i = 0; i < count; ++i)
		{
			D3D11RenderTarget* pTarget = new D3D11RenderTarget(m_pContext);
			if(pTarget->Create(w, h , format, miplvls) == false)
			{
				return false;
			}
			m_pRTViews[i] = pTarget->GetD3D11RenderTargetView();
			m_RTs.push_back(RenderTargetPtr(pTarget));
		}

		return true;
	}
	ID3D11DepthStencilView* D3D11MultiRenderTarget::GetD3D11DepthStencilView()
	{
		if(m_pDepthBuffer == nullptr)
		{
			return NULL;
		}
		return ((D3D11DepthStencilBuffer*)m_pDepthBuffer.get())->GetD3D11DepthStencilView();
	}
	ID3D11RenderTargetView** D3D11MultiRenderTarget::GetD3D11RenderTargetViews()
	{
		return m_pRTViews;
	}
	RenderTargetPtr D3D11MultiRenderTarget::GetRenderTarget(int index)
	{
		return m_RTs[index];
	}
}
