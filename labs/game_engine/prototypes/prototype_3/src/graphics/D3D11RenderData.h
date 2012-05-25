#pragma once


#include "graphics\RenderData.h"

namespace engine
{
	class D3D11RenderData : public RenderData
	{
	public:
		D3D11RenderData(ID3D11DeviceContext* pContext);
		virtual ~D3D11RenderData(void);

		void										Release();

		bool										AllocIndexBuffer(unsigned int bytes, void* pInitData, bool dynamic);
		bool										AllocVertexBuffer(unsigned int bytes, void* pInitData, bool dynamic);
		void*										MapVertexBuffer(MAP_HINT hint);
		void										UnmapVertexBuffer();

		void*										MapIndexBuffer(MAP_HINT hint);
		void										UnmapIndexBuffer();

		void										SetTransform(const math::Matrix44& transform);

		void										SetShader(ShaderPtr pShader);


		ID3D11Buffer*								GetD3DVertexBuffer();
		ID3D11Buffer*								GetD3DIndexBuffer();

	private:
		void*										MapBuffer(ID3D11Buffer* pBuffer, MAP_HINT hint);
		void										UnmapBuffer(ID3D11Buffer* pBuffer);
	private:

		ID3D11DeviceContext*						m_pContext;

		ID3D11Buffer*								m_pVertexBuffer;
		ID3D11Buffer*								m_pIndexBuffer;

		ShaderPtr									m_pShader;

		math::Matrix44								m_worldTransform;
	};

}
