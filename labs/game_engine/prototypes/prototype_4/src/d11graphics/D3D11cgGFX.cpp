#include "d11graphics_pch.h"
#include "D3D11cgGFX.h"

namespace engine
{
	D3D11cgGFX::D3D11cgGFX(CGcontext pCG, ID3D11DeviceContext* pContext)
	{
		m_pCG = pCG;

		m_pEffect = NULL;

		m_pIL							= NULL;
		m_pTechnique					= NULL;
		m_pPass							= NULL;

		m_pContext						= pContext;
	}


	D3D11cgGFX::~D3D11cgGFX(void)
	{
	}


	bool D3D11cgGFX::LoadFromFile(const char* szFile)
	{
		HRESULT hr = S_OK;

		char buffer[128];
		m_pEffect = cgCreateEffectFromFile( m_pCG, szFile, NULL );
		
		CGerror error;
		const char *string = cgGetLastErrorString(&error);

		static char szError[1024];
		if( error != CG_NO_ERROR ) 
		{
			if( error == CG_COMPILER_ERROR ) 
			{
				sprintf(szError,
					"Program: %s\n"
					"Error: %s\n\n"
					"Cg compiler output...\n%s",
					szFile, string,
					cgGetLastListing(m_pCG));
			} 
			else 
			{
				sprintf(szError,
	                "Program: %s\n"
					"Error: %s",
					szFile, string);
			}

			OutputDebugStringA(szError);
			OutputDebugStringA("\n");

		}
   
		if(m_pEffect == NULL)
		{
			return false;
		}

		CGtechnique pTechnique = cgGetFirstTechnique( m_pEffect );
		while( pTechnique && cgValidateTechnique( pTechnique ) == CG_FALSE ) 
		{
			pTechnique = cgGetNextTechnique( pTechnique );
		}
			
		
		m_pTechnique = pTechnique;
		
		m_pPass = NULL;

		return m_pTechnique != NULL;
	}
	void D3D11cgGFX::Release()
	{
		if(m_pIL)
		{
			m_pIL->Release();
			m_pIL = NULL;
		}
		m_pPass = NULL;
		m_pTechnique = NULL;

		cgDestroyEffect( m_pEffect );
		m_pEffect = NULL;

		m_pCG = NULL;
		m_pContext = NULL;
	}


	
	bool D3D11cgGFX::SetVertexFormat(VertexElement format[], uint32 nElem)
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
			layout[i].AlignedByteOffset						= 0;
			layout[i].InputSlotClass						= D3D11_INPUT_PER_VERTEX_DATA;
			layout[i].InstanceDataStepRate					= 0;
		}
		
		CGpass pass = cgGetFirstPass( m_pTechnique );

		ID3D10Blob * pVSBuf = cgD3D11GetIASignatureByPass( pass );


		//DXGI_FORMAT_R32G32B32_FLOAT
		ID3D11Device* pDevice = NULL;

		m_pContext->GetDevice(&pDevice);

		if(pDevice == NULL)
		{
			return false;
		}

		HRESULT hr = pDevice->CreateInputLayout( layout, nElem, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pIL ); 

		pVSBuf->Release();
		delete []layout;
		pDevice->Release();

		if(FAILED(hr))
		{
			return false;
		}
		
		return true;
	}


	bool D3D11cgGFX::BeginPass()
	{
		if(m_pPass == NULL)
		{
			m_pPass = cgGetFirstPass(m_pTechnique);
		}
		else
		{
			m_pPass = cgGetNextPass(m_pPass);
		}
		
		return m_pPass != NULL;
	}
	void D3D11cgGFX::EndPass()
	{
		if(m_pPass != NULL)
		{
			//cgResetPassState(m_pPass);
		}
	}
	void D3D11cgGFX::ApplyPass()
	{
		cgSetPassState(m_pPass);
	}
	void D3D11cgGFX::SetMatrixByName(const char* szParam, const math::Matrix44& mat)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szParam);

		if(param == NULL)
		{
			return;
		}

		cgSetMatrixParameterfr(param, mat.m);
	}
	void D3D11cgGFX::SetMatrixBySemantic(const char* szSemantic, const math::Matrix44& mat)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szSemantic);

		if(param == NULL)
		{
			return;
		}

		cgSetMatrixParameterfr(param, mat.m);
	}
	void D3D11cgGFX::SetTextureByName(const char* szName, TexturePtr pTex)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}


		//cgD3D11SetTextureParameter(param, pTex);
	}

	void D3D11cgGFX::SetVectorByName(const char* szName, const math::Vector3& v)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter3f(param, v.x, v.y, v.z);
	}
	void D3D11cgGFX::SetVectorByName(const char* szName, const math::Vector4& v)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter4f(param, v.x, v.y, v.z, v.w);
	}
	void D3D11cgGFX::SetVectorByName(const char* szName, const math::Vector2& v)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter2f(param, v.x, v.y);
	}
	void D3D11cgGFX::SetFloatByName(const char* szName, float v)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter1f(param, v);
	}
	void D3D11cgGFX::SetIntByName(const char* szName, int v)
	{
		CGparameter param = cgGetNamedEffectParameter(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter1i(param, v);
	}
	void D3D11cgGFX::SetTextureBySemantic(const char* szName, TexturePtr pTex)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		//cgSetTextureParameter(param, mat.m);
	}
	void D3D11cgGFX::SetVectorBySemantic(const char* szName, const math::Vector3& v)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter3f(param, v.x, v.y, v.z);
	}
	void D3D11cgGFX::SetVectorBySemantic(const char* szName, const math::Vector4& v)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter4f(param, v.x, v.y, v.z, v.w);
	}
	void D3D11cgGFX::SetVectorBySemantic(const char* szName, const math::Vector2& v)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter2f(param, v.x, v.y);
	}
	void D3D11cgGFX::SetFloatBySemantic(const char* szName, float v)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter1f(param, v);
	}
	void D3D11cgGFX::SetIntBySemantic(const char* szName, int v)
	{
		CGparameter param = cgGetEffectParameterBySemantic(m_pEffect, szName);

		if(param == NULL)
		{
			return;
		}

		cgSetParameter1i(param, v);
	}
	void D3D11cgGFX::ApplyVertexFormat()
	{
		m_pContext->IASetInputLayout(m_pIL);
	}
}
