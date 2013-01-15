#pragma once

#include "core\Texture.h"

namespace ld3d
{
	class D3D11Texture : public Texture
	{
	public:
		D3D11Texture(ID3D11DeviceContext* pContext);
		virtual ~D3D11Texture(void);


		bool								CreateFromRes(ID3D11Resource* pRes, G_FORMAT view_format = G_FORMAT_UNKNOWN);
		bool								LoadFromFile(const char* szFile);
		ID3D11Resource*						GetD3D11Resource();

		TEXTURE_TYPE						GetType();
		void								Release();

		ID3D11ShaderResourceView*			GetShaderResourceView();

	private:
		ID3D11Resource*						m_pTex;

		ID3D11ShaderResourceView*			m_pShaderView;
		ID3D11DeviceContext*				m_pContext;
		ID3D11Device*						m_pDevice;
		TEXTURE_TYPE						m_type;

	};
}
