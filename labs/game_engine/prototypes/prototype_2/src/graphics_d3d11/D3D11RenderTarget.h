#pragma once


#include "graphics\RenderTarget.h"

namespace engine
{
	class D3D11RenderTarget : public RenderTarget
	{
	public:
		D3D11RenderTarget(void);
		virtual ~D3D11RenderTarget(void);

		void											Initialize(ID3D11RenderTargetView* pView);
		ID3D11RenderTargetView*							GetD3DRenderTargetView();

		void											Release();

	private:

		ID3D11RenderTargetView*							m_pRenderTarget;

	};


}