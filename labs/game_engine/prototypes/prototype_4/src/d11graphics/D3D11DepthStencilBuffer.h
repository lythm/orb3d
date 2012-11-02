#pragma once

#include "core\DepthStencilBuffer.h"

namespace engine
{
	class D3D11DepthStencilBuffer : public DepthStencilBuffer
	{
	public:
		D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext);
		virtual ~D3D11DepthStencilBuffer(void);

		bool							Create(TexturePtr pTex);

		void							Release();

		ID3D11DepthStencilView*			GetD3D11DepthStencilView();

		TexturePtr						AsTexture();

		void							Clear(float depth, int stencil);
	private:
		ID3D11DeviceContext*						m_pContext;
		ID3D11Device*								m_pDevice;
		ID3D11DepthStencilView*						m_pDepthStencilView;

		TexturePtr									m_pTex;
	};


}