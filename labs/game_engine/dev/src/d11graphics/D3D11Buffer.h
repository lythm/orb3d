#pragma once


#include "core\GPUBuffer.h"


namespace ld3d
{
	class D3D11Buffer : public GPUBuffer
	{
	public:
		D3D11Buffer(ID3D11Buffer* pBuffer, ID3D11DeviceContext* pContext);
		virtual ~D3D11Buffer(void);


		void*											Map(MAP_HINT hint);
		void											Unmap();
		void											Release();

		ID3D11Buffer*									GetD3D11BufferInterface();

	private:
		ID3D11Buffer*									m_pBuffer;
		ID3D11DeviceContext*							m_pContext;
	};
}
