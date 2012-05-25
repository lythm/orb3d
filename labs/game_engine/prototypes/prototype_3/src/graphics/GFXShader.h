#pragma once

#include "graphics\Shader.h"


#include <Cg\cgD3D11.h>



namespace engine
{
	class CGFXShader : public Shader
	{
	public:
		CGFXShader(CGcontext pCG);
		virtual ~CGFXShader(void);


		bool								LoadFromFile(const char* szFile);
		void								Release();

		void								SetParameter();
		void								SetTexture();

		void								SetVertexFormat(VertexElement format[], uint32 nElem);

	private:

		CGtechnique							m_pTechnique;
		CGcontext							m_pCG;

		CGeffect							m_pEffect;

		ID3D11InputLayout*					m_pIL;
	};


}