#pragma once

#include "graphics\GraphicsFX.h"

namespace engine
{
	class D3D11GraphicsFX : public GraphicsFX
	{
	public:
		struct Pass
		{
			ID3D11Buffer*								m_pVertexShaderConstantBuffer;
			ID3D11VertexShader*							m_pVertexShader;
			ID3D11PixelShader*							m_pPixelShader;
		};
		

		D3D11GraphicsFX(ID3D11DeviceContext* pContext);
		virtual ~D3D11GraphicsFX(void);

		void											Release();
		

		bool											Begin(uint32& passCount);

		void											ApplyPass(uint32 iPass);

		void											End();

		
		ID3D11InputLayout*								GetInputLayout();


	private:


	private:

		std::vector<Pass>								m_PassArray;

		ID3D11DeviceContext*							m_pContext;
		ID3D11InputLayout*								m_pInputLayout;
	};
}
