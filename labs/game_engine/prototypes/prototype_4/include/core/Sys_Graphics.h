#pragma once

#include "math/math_all.h"

namespace engine
{
	class Sys_Graphics
	{
	public:

		enum BUFFER_TYPE
		{
			BT_VERTEX_BUFFER,
			BT_INDEX_BUFFER,
			BT_CONSTANT_BUFFER,
		};

		enum PRIMITIVE_TYPE
		{
			PT_TRIANGLE_LIST,
		};

		enum INDEX_TYPE
		{
			IT_INT16,
			IT_INT32,
		};

		virtual bool									Initialize(void* app_handle, 
																uint32 width, 
																uint32 height)										= 0;

		virtual void									Release()													= 0;
		
		virtual void									DrawPrimitive(int count, 
																int startindex, 
																int basevertex)										= 0;
		virtual void									SetPrimitiveType(PRIMITIVE_TYPE pt)							= 0;
		
		virtual void									SetClearColor(const math::Color4& clr)						= 0;
		virtual void									SetClearDepth(float d)										= 0;
		virtual void									SetClearStencil(uint32 val)									= 0;

		virtual void									ClearRenderTarget()											= 0;
				
		virtual void									Present()													= 0;

		virtual GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, 
																	int bytes, 
																	void* pInitData, 
																	bool dynamic)									= 0;

		virtual void									SetIndexBuffer(GPUBufferPtr pBuffer, INDEX_TYPE type)		= 0;
		virtual void									SetVertexBuffer(GPUBufferPtr pBuffer, 
																	unsigned int offset, 
																	unsigned int stride)							= 0;

		virtual GFXPtr									CreateGFXFromFile(const char* szFile)						= 0;
		

	protected:
		Sys_Graphics(void){}
		virtual ~Sys_Graphics(void){}
	};


}
