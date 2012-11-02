#pragma once

#include "math/math_all.h"

#include "core/g_format.h"

namespace engine
{
	class Sys_Graphics
	{
	public:

		enum CLEAR_RENDERTARGET_FLAG
		{
			CLEAR_COLOR_BUFFER					= 0x01,
			CLEAR_DEPTHSTENCIL_BUFFER			= 0x02,
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

		virtual void									ClearFrameBuffer(CLEAR_RENDERTARGET_FLAG flag = 
																	CLEAR_RENDERTARGET_FLAG(
																	CLEAR_COLOR_BUFFER 
																	| CLEAR_DEPTHSTENCIL_BUFFER))					= 0;

		virtual void									Present()													= 0;

		virtual GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, 
																	int bytes, 
																	void* pInitData, 
																	bool dynamic)									= 0;

		virtual void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type)			= 0;
		virtual void									SetVertexBuffer(GPUBufferPtr pBuffer, 
																	unsigned int offset, 
																	unsigned int stride)							= 0;

		virtual GFXPtr									CreateGFXFromFile(const char* szFile)						= 0;
		
		virtual TexturePtr								CreateTextureFromFile(const char* szFile)					= 0;

		virtual void									SetRenderTarget(RenderTargetPtr pRenderTarget, 
																	DepthStencilBufferPtr pDS)						= 0;

		virtual void									SetRenderTargets(const std::vector<RenderTargetPtr>& pTargets, 
																	DepthStencilBufferPtr pDS)						= 0;

		virtual RenderTargetPtr							CreateRenderTarget(TexturePtr pColorBuffer)					= 0;
		virtual DepthStencilBufferPtr					CreateDepthStencilBuffer()									= 0;

	protected:
		Sys_Graphics(void){}
		virtual ~Sys_Graphics(void){}
	};


}
