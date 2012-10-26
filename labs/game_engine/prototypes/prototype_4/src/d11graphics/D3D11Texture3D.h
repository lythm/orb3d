#pragma once

#include "core\Texture3D.h"


namespace engine
{
	class D3D11Texture3D : public Texture3D
	{
	public:
		D3D11Texture3D(ID3D11Texture3D* pTex);
		virtual ~D3D11Texture3D(void);

		ID3D11Texture3D*					GetD3D11Resource();

		
	private:
		ID3D11Texture3D*					m_pTex;
	};


}