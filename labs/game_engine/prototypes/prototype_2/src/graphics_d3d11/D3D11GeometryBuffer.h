#pragma once


#include "graphics\GeometryBuffer.h"

namespace engine
{
	class D3D11GeometryBuffer : public GeometryBuffer
	{
	public:
		
		
		D3D11GeometryBuffer(ID3D11DeviceContext* pContext);
		virtual ~D3D11GeometryBuffer(void);


		bool											AllocVertexBuffer(unsigned int bytes, bool dynamic = false);
		void											FreeVertexBuffer();

		bool											AllocIndexBuffer(unsigned int bytes, bool dynamic = false);
		void											FreeIndexBuffer();

		void*											MapVertexBuffer(MAP_HINT hint);
		void											UnmapVertexBuffer();

		void*											MapIndexBuffer(MAP_HINT hint);
		void											UnmapIndexBuffer();

		ID3D11Buffer*									GetD3DVertexBuffer();
		ID3D11Buffer*									GetD3DIndexBuffer();

		void											Apply(uint32 vertexBufferoffset, uint32 vertexBufferstride, uint32 indexBufferOffset);
		void											Apply(uint32 vertexStride);
	private:
		void*											MapBuffer(ID3D11Buffer* pBuffer, MAP_HINT hint);
		void											UnmapBuffer(ID3D11Buffer* pBuffer);
	private:

		ID3D11Buffer*									m_pVertexBuffer;
		ID3D11Buffer*									m_pIndexBuffer;


		ID3D11DeviceContext*							m_pContext;
	};
}
