#pragma once

#include "core\GFX.h"

#include "core\VertexFormat.h"

namespace engine
{
	class D3D11cgGFX : public GFX
	{
	public:
		D3D11cgGFX(CGcontext pCG);
		virtual ~D3D11cgGFX(void);


		bool								BeginPass();
		void								ApplyPass();
		bool								NextPass();
		void								EndPass();
		

		void								Release();

		bool								LoadFromFile(const char* szFile);
		void								SetParameter();
		void								SetTexture();

		bool								SetVertexFormat(VertexElement format[], uint32 nElem);

	private:
		CGcontext							m_pCG;

		CGtechnique							m_pTechnique;
		CGeffect							m_pEffect;
		ID3D11InputLayout*					m_pIL;

		CGpass								m_pPass;

	};


}