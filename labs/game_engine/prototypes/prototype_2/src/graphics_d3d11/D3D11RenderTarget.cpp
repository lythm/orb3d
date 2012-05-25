#include "graphics_pch.h"
#include "D3D11RenderTarget.h"


namespace engine
{
	D3D11RenderTarget::D3D11RenderTarget(void)
	{
		m_pRenderTarget = NULL;
	}


	D3D11RenderTarget::~D3D11RenderTarget(void)
	{
	}
	ID3D11RenderTargetView*	D3D11RenderTarget::GetD3DRenderTargetView()
	{
		return m_pRenderTarget;
	}
	void D3D11RenderTarget::Release()
	{
		if(m_pRenderTarget != NULL)
		{
			m_pRenderTarget->Release();
			m_pRenderTarget = NULL;
		}
	}
	void D3D11RenderTarget::Initialize(ID3D11RenderTargetView* pView)
	{
		m_pRenderTarget = pView;
	}
}
