#pragma once

#include "core\Texture2D.h"

namespace engine
{
	class D3D11Texture2D : public Texture2D
	{
	public:
		D3D11Texture2D(ID3D11Resource* pTex);
		virtual ~D3D11Texture2D(void);



		ID3D11Resource*					GetD3D11Resource();

		
	private:
		ID3D11Resource*					m_pTex;
	};
}
