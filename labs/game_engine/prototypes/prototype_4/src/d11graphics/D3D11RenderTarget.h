#pragma once


#include "core\RenderTarget.h"



namespace engine
{
	class D3D11RenderTarget : public RenderTarget
	{
	public:
		D3D11RenderTarget(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderTarget(void);


		void SetColorBuffer(TexturePtr pTex);

		ID3D11RenderTargetView*						GetRenderTargetView();

	private:

		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;
		ID3D11RenderTargetView*						m_pRenderTargetView;
	};
}
