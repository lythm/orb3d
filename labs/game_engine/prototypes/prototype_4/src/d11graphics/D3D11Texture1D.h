#pragma once

#include "core\Texture1D.h"

namespace engine
{
	class D3D11Texture1D : public Texture1D
	{
	public:
		D3D11Texture1D(ID3D11Texture1D* pTex);
		virtual ~D3D11Texture1D(void);

		ID3D11Texture1D*					GetD3D11Resource();

		
	private:
		ID3D11Texture1D*					m_pTex;
	};


}