#include "d11graphics_pch.h"
#include "D3D11EffectGFX.h"

namespace engine
{
	D3D11EffectGFX::D3D11EffectGFX(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;
	}


	D3D11EffectGFX::~D3D11EffectGFX(void)
	{

	}

	bool D3D11EffectGFX::LoadFromFile(const char* szFile)
	{
		ID3D10Blob* pBlob = NULL;
		ID3D10Blob* pErrorBlob = NULL;

		if( FAILED( D3DX11CompileFromFileA( szFile, NULL, NULL, NULL, "fx_5_0", D3DCOMPILE_ENABLE_STRICTNESS, NULL, NULL, &pBlob, &pErrorBlob, NULL ) ) )
		{
			const char* szTxt =(char*) pErrorBlob->GetBufferPointer();
			return false;
		}

		if(pErrorBlob)
		{
			const char* szTxt =(char*) pErrorBlob->GetBufferPointer();
			int i = 0;
		}
		ID3D11Device* pDevice = NULL;
		
		m_pContext->GetDevice(&pDevice);

		ID3DX11Effect* pEffect = NULL;

		HRESULT ret = D3DX11CreateEffectFromMemory(pBlob->GetBufferPointer(), pBlob->GetBufferSize(),  0, pDevice, &pEffect);
		if(FAILED(ret))
		{
			return false;
		}

		return true;
	}


	void D3D11EffectGFX::ApplyVertexFormat()
	{
	}

	bool D3D11EffectGFX::BeginPass()
	{
		return true;
	}
	void D3D11EffectGFX::ApplyPass()
	{
	}
	void D3D11EffectGFX::EndPass()
	{
	}
		
	void D3D11EffectGFX::Release()
	{
	}
		
	void D3D11EffectGFX::SetMatrixByName(const char* szParam, const math::Matrix44& mat)
	{
	}
	void D3D11EffectGFX::SetTextureByName(const char* szName, TexturePtr pTex)
	{
	}
	void D3D11EffectGFX::SetVectorByName(const char* szName, const math::Vector3& v)
	{
	}
	void D3D11EffectGFX::SetVectorByName(const char* szName, const math::Vector4& v)
	{
	}
	void D3D11EffectGFX::SetVectorByName(const char* szName, const math::Vector2& v)
	{
	}
	void D3D11EffectGFX::SetFloatByName(const char* szName, float v)
	{
	}
	void D3D11EffectGFX::SetIntByName(const char* szName, int v)
	{
	}

	void D3D11EffectGFX::SetMatrixBySemantic(const char* szSemantic, const math::Matrix44& mat)
	{
	}
	void D3D11EffectGFX::SetTextureBySemantic(const char* szName, TexturePtr pTex)
	{
	}
	void D3D11EffectGFX::SetVectorBySemantic(const char* szName, const math::Vector3& v)
	{
	}
	void D3D11EffectGFX::SetVectorBySemantic(const char* szName, const math::Vector4& v)
	{
	}
	void D3D11EffectGFX::SetVectorBySemantic(const char* szName, const math::Vector2& v)
	{
	}
	void D3D11EffectGFX::SetFloatBySemantic(const char* szName, float v)
	{
	}
	void D3D11EffectGFX::SetIntBySemantic(const char* szName, int v)
	{
	}

	bool D3D11EffectGFX::SetVertexFormat(VertexElement format[], uint32 nElem)
	{
		return true;
	}
}

