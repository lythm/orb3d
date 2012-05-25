#include "graphics_pch.h"
#include "GFXShader.h"




namespace engine
{

	CGFXShader::CGFXShader(CGcontext pCG)
	{
		m_pCG = pCG;

		m_pEffect = NULL;

		m_pIL							= NULL;
		m_pTechnique					= NULL;
	}


	CGFXShader::~CGFXShader(void)
	{
	}
	bool CGFXShader::LoadFromFile(const char* szFile)
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
			
		if( pTechnique == NULL) 
		{
			return false;
		}
		m_pTechnique = pTechnique;
		
		return true;
	}
	void CGFXShader::Release()
	{
		if(m_pIL)
		{
			m_pIL->Release();
			m_pIL = NULL;
		}
		cgDestroyEffect( m_pEffect );
		m_pEffect = NULL;
	}

	void CGFXShader::SetParameter()
	{
	}
	void CGFXShader::SetTexture()
	{
	}
	void CGFXShader::SetVertexFormat(VertexElement format[], uint32 nElem)
	{
		if(m_pIL != NULL)
		{
			m_pIL->Release();
		}
		//DXGI_FORMAT_R32G32B32_FLOAT
		ID3D11Device* pDevice = cgD3D11GetDevice(m_pCG);

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

		pDevice->CreateInputLayout( layout, nElem, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &m_pIL ); 
		
	}
}
