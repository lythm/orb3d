#include "d11graphics_pch.h"
#include "D3D11EffectMaterial.h"
#include "D3D11Texture.h"
#include "D3D11Format.h"
#include "D3D11Buffer.h"
#include "D3D11RenderTarget.h"

namespace ld3d
{
	D3D11EffectMaterial::D3D11EffectMaterial(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		m_pContext->GetDevice(&m_pDevice);
		m_pIL = NULL;
		m_pEffect = NULL;

		m_pTech	 = NULL;

		m_worldTM.MakeIdentity();
		m_viewTM.MakeIdentity();
		m_projTM.MakeIdentity();
	}


	D3D11EffectMaterial::~D3D11EffectMaterial(void)
	{

	}
	void D3D11EffectMaterial::OutputDebugInfo(ID3D10Blob* pBlob)
	{
		if(pBlob)
		{
			const char* szTxt =(char*) pBlob->GetBufferPointer();
			OutputDebugStringA("[D3D11Material Compiler]:\n");
			OutputDebugStringA(szTxt);
			pBlob->Release();
		}
	}
	bool D3D11EffectMaterial::LoadFromFile(const char* szFile)
	{
		ID3D10Blob* pBlob = NULL;
		ID3D10Blob* pErrorBlob = NULL;

		if( FAILED( D3DX11CompileFromFileA( szFile, NULL, NULL, NULL, "fx_5_0", D3DCOMPILE_ENABLE_STRICTNESS, NULL, NULL, &pBlob, &pErrorBlob, NULL ) ) )
		{
			OutputDebugInfo(pErrorBlob);
			
			return false;
		}

		OutputDebugInfo(pErrorBlob);

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


		m_semantics.m_pViewTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_VIEW");
		m_semantics.m_pWorldTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_WORLD");
		m_semantics.m_pProjTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_PROJ");

		m_semantics.m_pInvViewTM				= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_VIEW");
		m_semantics.m_pInvWorldTM				= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_WORLD");
		m_semantics.m_pInvProjTM				= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_PROJ");

		m_semantics.m_pWVTM						= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_WV");
		m_semantics.m_pWVPTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_WVP");

		m_semantics.m_pInvWVTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_WV");
		m_semantics.m_pInvWVPTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_WVP");
		m_semantics.m_pInvVPTM					= (ID3DX11EffectMatrixVariable*)m_pEffect->GetVariableBySemantic("MATRIX_I_VP");


		m_semantics.m_pGBuffer					= (ID3DX11EffectShaderResourceVariable*)m_pEffect->GetVariableBySemantic("DR_GBUFFER");
		m_semantics.m_pABuffer					= (ID3DX11EffectShaderResourceVariable*)m_pEffect->GetVariableBySemantic("DR_ABUFFER");
		return true;
	}
	bool D3D11EffectMaterial::SelectTechByName(const char* szName)
	{
		ID3DX11EffectTechnique* pTech = m_pEffect->GetTechniqueByName(szName);
		if(pTech == NULL)
		{
			return false;
		}
		if(FALSE == pTech->IsValid())
		{
			return false;
		}
		m_pTech = pTech;

		return true;
	}

	void D3D11EffectMaterial::ApplyVertexFormat()
	{
		m_pContext->IASetInputLayout(m_pIL);
	}
	void D3D11EffectMaterial::UpdateSemantics()
	{
		if(m_semantics.m_pProjTM)
		{
			m_semantics.m_pProjTM->SetMatrix(m_projTM.m);
		}

		if(m_semantics.m_pWorldTM)
		{
			m_semantics.m_pWorldTM->SetMatrix(m_worldTM.m);
		}

		if(m_semantics.m_pViewTM)
		{
			m_semantics.m_pViewTM->SetMatrix(m_viewTM.m);
		}

		if(m_semantics.m_pWVPTM)
		{
			m_semantics.m_pWVPTM->SetMatrix((m_worldTM * m_viewTM * m_projTM).m);
		}

		if(m_semantics.m_pWVTM)
		{
			m_semantics.m_pWVTM->SetMatrix((m_worldTM * m_viewTM).m);
		}


		math::Matrix44 invWorld = math::MatrixInverse(m_worldTM);
		math::Matrix44 invView = math::MatrixInverse(m_viewTM);
		math::Matrix44 invProj = math::MatrixInverse(m_projTM);
		math::Matrix44 invWVP = math::MatrixInverse(m_worldTM * m_viewTM * m_projTM);
		math::Matrix44 invWV = math::MatrixInverse(m_worldTM * m_viewTM);
		math::Matrix44 invVP = math::MatrixInverse(m_viewTM * m_projTM);

		if(m_semantics.m_pInvWorldTM)
		{
			m_semantics.m_pInvWorldTM->SetMatrix(invWorld.m);
		}

		if(m_semantics.m_pInvViewTM)
		{
			m_semantics.m_pInvViewTM->SetMatrix(invView.m);
		}
		if(m_semantics.m_pInvProjTM)
		{
			m_semantics.m_pInvProjTM->SetMatrix(invProj.m);
		}

		if(m_semantics.m_pInvWVPTM)
		{
			m_semantics.m_pInvWVPTM->SetMatrix(invWVP.m);
		}
		if(m_semantics.m_pInvWVTM)
		{
			m_semantics.m_pInvWVTM->SetMatrix(invWV.m);
		}
		if(m_semantics.m_pInvVPTM)
		{
			m_semantics.m_pInvVPTM->SetMatrix(invVP.m);
		}

	}
	bool D3D11EffectMaterial::Begin(int& nPass)
	{
		nPass = m_nPass;
		UpdateSemantics();
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
	void D3D11EffectMaterial::End()
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

		pView = ((D3D11Texture*)pTex.get())->GetShaderResourceView();

		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		if(pVal)
		{
			pVal->AsShaderResource()->SetResource(pView);
		}
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector3& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		pVal->AsVector()->SetFloatVector(v.v);

		//m_pEffect->GetVariableByName(szName)->AsScalar()->SetFloatArray(v.v, 0, 3);
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector4& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		pVal->AsVector()->SetFloatVector(v.v);
	}
	void D3D11EffectMaterial::SetVectorByName(const char* szName, const math::Vector2& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		pVal->AsVector()->SetFloatVector(v.v);
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
			pVal->AsVector()->SetFloatVector(v.v);
		}

	}
	void D3D11EffectMaterial::SetVectorBySemantic(const char* szName, const math::Vector4& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsVector()->SetFloatVector(v.v);
		}
	}
	void D3D11EffectMaterial::SetVectorBySemantic(const char* szName, const math::Vector2& v)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableBySemantic(szName);
		if(pVal)
		{
			pVal->AsVector()->SetFloatVector(v.v);
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
	void D3D11EffectMaterial::SetCBByName(const char* szName, void* buffer, int size)
	{
		ID3DX11EffectVariable* pVal = m_pEffect->GetVariableByName(szName);
		if(pVal)
		{
			pVal->SetRawValue(buffer, 0, size);
			//ID3D11Buffer* pD3DBuffer = nullptr;
			//pVal->AsConstantBuffer()->GetConstantBuffer(&pD3DBuffer);
			//pVal->AsConstantBuffer()->SetConstantBuffer(((D3D11Buffer*)pCB.get())->GetD3D11BufferInterface());

			//D3D11_MAPPED_SUBRESOURCE desc;
			//m_pContext->Map(pD3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &desc);

			//memcpy(desc.pData, buffer, size);

			//m_pContext->Unmap(pD3DBuffer, 0);
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

	void D3D11EffectMaterial::SetViewMatrix(const math::Matrix44& val)
	{
		m_viewTM = val;
	}
	void D3D11EffectMaterial::SetProjMatrix(const math::Matrix44& val)
	{
		m_projTM = val;
	}
	void D3D11EffectMaterial::SetWorldMatrix(const math::Matrix44& val)
	{
		m_worldTM = val;
	}
	void D3D11EffectMaterial::SetGBuffer(RenderTargetPtr pGBuffer)
	{
		if(m_semantics.m_pGBuffer == nullptr)
		{
			return;
		}
		D3D11Texture* pTex1 = (D3D11Texture*)(pGBuffer->AsTexture(0).get());
		D3D11Texture* pTex2 = (D3D11Texture*)(pGBuffer->AsTexture(1).get());
		D3D11Texture* pTex3 = (D3D11Texture*)(pGBuffer->AsTexture(2).get());


		ID3D11ShaderResourceView* pBuffers[3] = {
			pTex1->GetShaderResourceView(),
			pTex2->GetShaderResourceView(),
			pTex3->GetShaderResourceView(),
		};

		m_semantics.m_pGBuffer->SetResourceArray(pBuffers, 0, 3);

	}
	void D3D11EffectMaterial::SetABuffer(RenderTargetPtr pABuffer)
	{
		if(m_semantics.m_pABuffer == nullptr)
		{
			return;
		}
		D3D11Texture* pTex1 = (D3D11Texture*)(pABuffer->AsTexture(0).get());

		m_semantics.m_pABuffer->SetResource(pTex1->GetShaderResourceView());
	}
}

