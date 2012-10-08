#pragma once


#include "core\Sys_Graphics.h"

namespace engine
{
	class OGL4Graphics : public Sys_Graphics
	{
	public:
		OGL4Graphics(void);
		virtual ~OGL4Graphics(void);


		bool									Initialize(void* app_handle, uint32 width, uint32 height);
		void									Release();

		void									Draw(RenderDataPtr pData);
		void									Render();

		void									SetViewTransform(const math::Matrix44& view);
		void									SetProjTransform(const math::Matrix44& proj);

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(uint32 val);

		void									ClearRenderTarget();
				
		void									Present();


		void									SetIndexBuffer(GPUBufferPtr pBuffer);
		void									SetVertexBuffer(GPUBufferPtr pBuffer);

		GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic);

		GFXPtr									CreateGFXFromFile(const char* szFile);
	};


}
