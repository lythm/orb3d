#include "d11graphics_pch.h"
#include "D3D11EffectMaterial.h"
#include "D3D11Texture.h"
#include "D3D11Format.h"
#include "D3D11Buffer.h"

namespace engine
{
	D3D11EffectMaterial::D3D11EffectMaterial(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		m_pContext->GetDevice(&m_pDevice);
		m_pIL = NULL;
		m_pEffect = NULL;

		m_pTech	 = NULL;
	}


	D3D11EffectMaterial::~D3D11EffectMaterial(void)
	{

	}

	bool D3D11EffectMaterial::LoadFromFile(const char* szFile)
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
			return false;
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


	void D3D11EffectMaterial::ApplyVertexFormat()
	{
		m_pContext->IASetInputLayout(m_pIL);
	}

	bool D3D11EffectMaterial::BeginPass(int& nPass)
	{

		nPass = m_nPass;

		return nPass != 0;
	}
	int D3D11EffectMaterial::FindPass(const std::string& name)
	{
		ID3DX11EffectPass* pPass = m_pTech->GetPassByName(name.c_str());

		if(pPass == NULL)
		{
			return -1;
		}

		for(int i = 0; i < m_nPass; ++i)
		{
			ID3DX11EffectPass* pFind = m_pTech->GetPassByIndex(i);
			if(pFind == pPass)
			{
				return i;
			}
		}
		return -1;
	}
	void D3D11EffectMaterial::ApplyPass(int index)
	{
		ID3DX11EffectPass* pPass = m_pTech->GetPassByIndex(index);
		
		pPass->Apply(0, m_pContext);

	}
	void D3D11EffectMaterial::EndPass()
	{
	}
		
	void D3D11EffectMaterial::Release()
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
		
	void D3D11EffectMaterial::SetMatrixByName(const char* szParam, const math::Matrix44& mat)
	{
		m_pEffect->GetVariableByName(szParam)->AsMatrix()->SetMatrix(mat.m);
	}
	void D3D11EffectMaterial::SetTextureByName(const char* szName, TexturePtr pTex)
	{
		ID3D11ShaderResourceView* pView = NULL;

		pView = (pTex == TexturePtr() ? NULL : ((D3D11Texture*)pTex.get())->GetShaderResourceView());

		m_pEffect->GetVariableByName(szName)->AsShaderResource()->SetResource(pView);

		
	/*	if(pTex == TexturePtr())
		{
			ID3D11ShaderResourceView* pTmp[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, }; 
			m_pContext->PSSetShaderResources(0, _countof(pTmp), pTmp);
		}*/
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector3& v)
	{
		m_pEffect->GetVariableByName(szName)->AsScalar()->SetFloatArray(v.v, 0, 3);
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector4& v)
	{
		m_pEffect->GetVariableByName(szName)->AsScalar()->SetFloatArray(v.v, 0, 4);
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector2& v)
	{
		m_pEffect->GetVariableByName(szName)->AsScalar()->SetFloatArray(v.v, 0, 2);
	}
	void D3D11EffectMaterial::SetFloatByName(const char* szName, float v)
	{
		m_pEffect->GetVariableByName(szName)->AsScalar()->SetFloat(v);
	}
	void D3D11EffectMaterial::SetIntByName(const char* szName, int v)
	{
		m_pEffect->GetVariableByName(szName)->AsScalar()->SetInt(v);
	}

	void D3D11EffectMaterial::SetMatrixBySemantic(const char* szSemantic, const math::Matrix44& mat)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szSemantic);
		
		if(pVal)
		{
			pVal->AsMatrix()->SetMatrix(mat.m);
		}
	}
	void D3D11EffectMaterial::SetTextureBySemantic(const char* szName, TexturePtr pTex)
	{
		ID3D11ShaderResourceView* pView = NULL;

		pView = ((D3D11Texture*)pTex.get())->GetShaderResourceView();

		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsShaderResource()->SetResource(pView);
		}
	}
	void D3D11EffectMaterial::SetVectorBySemantic(const char* szName, const math::Vector3& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsScalar()->SetFloatArray(v.v, 0, 3);
		}
	}
	void D3D11EffectMaterial::SetVectorBySemantic(const char* szName, const math::Vector4& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsScalar()->SetFloatArray(v.v, 0, 4);
		}
	}
	void D3D11EffectMaterial::SetVectorBySemantic(const char* szName, const math::Vector2& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsScalar()->SetFloatArray(v.v, 0, 2);
		}
	}
	void D3D11EffectMaterial::SetFloatBySemantic(const char* szName, float v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsScalar()->SetFloat(v);
		}
	}
	void D3D11EffectMaterial::SetIntBySemantic(const char* szName, int v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsScalar()->SetInt(v);
		}
	}
	void D3D11EffectMaterial::SetCBBySemantic(const char* szName, GPUBufferPtr pCB)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsConstantBuffer()->SetConstantBuffer(((D3D11Buffer*)pCB.get())->GetD3D11BufferInterface());
		}
	}
	void D3D11EffectMaterial::SetCBByName(const char* szName, GPUBufferPtr pCB)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		if(pVal)
		{
			pVal->AsConstantBuffer()->SetConstantBuffer(((D3D11Buffer*)pCB.get())->GetD3D11BufferInterface());
		}
	}
	bool D3D11EffectMaterial::SetVertexFormat(const VertexFormat& format)
	{
		if(m_pIL != NULL)
		{
			m_pIL->Release();
		}

		int nElem = format.GetElementCount();
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[nElem];

		for(int i = 0; i < nElem; ++i)
		{
			const VertexElement& e = format.GetElement(i);

			switch(e.semantic)
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

			layout[i].Format								= D3D11Format::Convert(e.type);
			layout[i].SemanticIndex							= e.element_slot;

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
			delete[] layout;
			return false;
		}
		delete[] layout;
		return true;
	}
}

