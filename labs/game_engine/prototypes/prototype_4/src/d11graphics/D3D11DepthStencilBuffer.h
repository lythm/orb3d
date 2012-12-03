#pragma once

#include "core\DepthStencilBuffer.h"

namespace engine
{
	class D3D11DepthStencilBuffer : public DepthStencilBuffer
	{
	public:
		D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext);
		virtual ~D3D11DepthStencilBuffer(void);

		bool										Create(int w, int h, G_FORMAT format);

		void										Release();
		ID3D11DepthStencilView*						GetD3D11DepthStencilView();

		void										Clear(float depth, int stencil);
	private:

		TexturePtr									CreateTexture(G_FORMAT format);
	private:

		ID3D11Texture2D*							m_pBuffer;
		ID3D11DeviceContext*						m_pContext;
		ID3D11DepthStencilView*						m_pDepthStencilView;
	};
}
