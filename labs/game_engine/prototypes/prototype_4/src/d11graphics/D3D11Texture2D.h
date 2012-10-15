#pragma once

#include "core\Texture2D.h"

namespace engine
{
	class D3D11Texture2D : public Texture2D
	{
	public:
		D3D11Texture2D(void);
		virtual ~D3D11Texture2D(void);



		ID3D11Texture2D*					GetD3D11Resource();

	private:
		ID3D11Texture2D*					m_pTex;
	};


}
