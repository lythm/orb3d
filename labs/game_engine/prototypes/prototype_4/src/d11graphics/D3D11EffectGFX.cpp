#include "d11graphics_pch.h"
#include "D3D11EffectGFX.h"
#include "D3D11Texture.h"

namespace engine
{
	D3D11EffectGFX::D3D11EffectGFX(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		m_pContext->GetDevice(&m_pDevice);
		m_pIL = NULL;
		m_pEffect = NULL;

		m_pTech	 = NULL;

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

			pErrorBlob->Release();
		}
	
		HRESULT ret = D3DX11CreateEffectFromMemory(pBlob->GetBufferPointer(), pBlob->GetBufferSize(),  0, m_pDevice, &m_pEffect);
		if(FAILED(ret))
		{
			return false;
		}

		if(m_pEffect->IsValid() == FALSE)
		{
			m_pEffect->Release();
			m_pEffect = NULL;
			return false;
		}

		D3DX11_EFFECT_DESC desc;

		if(FAILED(m_pEffect->GetDesc(&desc)))
		{
			m_pEffect->Release();
			m_pEffect = NULL;
			return false;
		}


		for(UINT i = 0; i < desc.Techniques; ++i)
		{
			ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByIndex(i);

			if(TRUE == pTech->IsValid())
			{
				m_pTech = pTech;
				break;
			}
		}

		if(m_pTech == NULL)
		{
			m_pEffect->Release();
			m_pEffect = NULL;
			m_pTech = NULL;
		}

		D3DX11_TECHNIQUE_DESC tech;

		if(FAILED(m_pTech->GetDesc(&tech)))
		{
			m_pEffect->Release();
			m_pEffect = NULL;
			m_pTech = NULL;
		}
		m_nPass = tech.Passes;

		return true;
	}


	void D3D11EffectGFX::ApplyVertexFormat()
	{
		m_pContext->IASetInputLayout(m_pIL);
	}

	bool D3D11EffectGFX::BeginPass(int& nPass)
	{

		nPass = m_nPass;

		return nPass != 0;
	}
	void D3D11EffectGFX::ApplyPass(int index)
	{
		ID3DX11EffectPass* pPass = m_pTech->GetPassByIndex(index);
		
		pPass->Apply(0, m_pContext);

	}
	void D3D11EffectGFX::EndPass()
	{
	}
		
	void D3D11EffectGFX::Release()
	{
		m_pTech = NULL;
		if(m_pEffect)
		{
			m_pEffect->Release();
			m_pEffect = NULL;
		}

		if(m_pIL)
		{
			m_pIL->Release();
			m_pIL = NULL;
		}
		if(m_pDevice)
		{
			m_pDevice->Release();
			m_pDevice = NULL;
		}

		m_pContext = NULL;
	}
		
	void D3D11EffectGFX::SetMatrixByName(const char* szParam, const math::Matrix44& mat)
	{
		m_pEffect->GetVariableByName(szParam)->AsMatrix()->SetMatrix(mat.m);
	}
	void D3D11EffectGFX::SetTextureByName(const char* szName, TexturePtr pTex)
	{
		ID3D11ShaderResourceView* pView = NULL;

		pView = ((D3D11Texture*)pTex.get())->GetShaderResourceView();
		m_pEffect->GetVariableByName(szName)->AsShaderResource()->SetResource(pView);
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
		m_pEffect->GetVariableBySemantic(szSemantic)->AsMatrix()->SetMatrix(mat.m);
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
		if(m_pIL != NULL)
		{
			m_pIL->Release();
		}

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[nElem];

		for(uint32 i = 0; i < nElem; ++i)
		{
			switch(format[i].semantic)
			{
			case VertexElement::POSITION:
				layout[i].SemanticName							= "POSITION";
				break;

			case VertexElement::NORMAL:
				layout[i].SemanticName							= "NORMAL";
				break;

			case VertexElement::COLOR:
				layout[i].SemanticName							= "COLOR";
				break;

			case VertexElement::POSITION_T:
				layout[i].SemanticName							= "POSITIONT";
				break;

			case VertexElement::TEXCOORD:
				layout[i].SemanticName							= "TEXCOORD";
				break;

			default:
				break;

			}

			switch(format[i].type)
			{
			case VertexElement::VE_FLOAT1:
				layout[i].Format								= DXGI_FORMAT_R32_FLOAT;
				break;

			case VertexElement::VE_FLOAT2:
				layout[i].Format								= DXGI_FORMAT_R32G32_FLOAT;
				break;

			case VertexElement::VE_FLOAT3:
				layout[i].Format								= DXGI_FORMAT_R32G32B32_FLOAT;
				break;

			case VertexElement::VE_FLOAT4:
				layout[i].Format								= DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;

			case VertexElement::VE_UINT32:
				layout[i].Format								= DXGI_FORMAT_R32_UINT;
				break;

			default:
				break;

			}

			layout[i].SemanticIndex							= format[i].element_slot;

			layout[i].InputSlot								= 0;
			layout[i].AlignedByteOffset						= D3D11_APPEND_ALIGNED_ELEMENT ;
			layout[i].InputSlotClass						= D3D11_INPUT_PER_VERTEX_DATA;
			layout[i].InstanceDataStepRate					= 0;
		}

		ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByIndex(0);
		
		ID3DX11EffectPass* pPass = pTech->GetPassByIndex(0);
		

		D3DX11_PASS_DESC pass;
		ZeroMemory(&pass, sizeof(pass));
		HRESULT hr = pPass->GetDesc(&pass);

		hr = m_pDevice->CreateInputLayout( layout, 
			nElem, 
			pass.pIAInputSignature,
			pass.IAInputSignatureSize,
			&m_pIL ); 

		if(FAILED(hr))
		{
			return false;
		}

		return true;
	}
}

