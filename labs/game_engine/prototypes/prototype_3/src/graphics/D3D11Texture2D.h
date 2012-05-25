#pragma once

#include "graphics\Texture2D.h"

namespace engine
{
	class D3D11Texture2D : public Texture2D
	{
	public:
		D3D11Texture2D(ID3D11Resource* pTex);
		virtual ~D3D11Texture2D(void);

		void										Release();

		ID3D11Resource*								GetD3D11Resource();

		ID3D11RenderTargetView*						GetD3D11RenderTargetView();

	private:
		ID3D11Resource*								m_pTexture;

		ID3D11RenderTargetView*						m_pRenderTargetView;
	};


}
