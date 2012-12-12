#pragma once

#include "math/math_all.h"

#include "core/g_format.h"

namespace engine
{
	class Sys_Graphics
	{
	public:

		virtual const GraphicsSetting&					GetGraphicsSetting()										= 0;

		virtual bool									Initialize(const GraphicsSetting& setting)					= 0;

		virtual void									Release()													= 0;
		
		virtual void									Draw(int vertexCount, int baseVertex)						= 0;
		virtual void									DrawIndexed(int count, 
																	int startindex,
																	int basevertex)									= 0;
		virtual void									SetPrimitiveType(PRIMITIVE_TYPE pt)							= 0;
		
		virtual void									ClearRenderTarget(RenderTargetPtr pTarget, 
																	const math::Color4& clr)						= 0; 

		virtual void									ClearDepthStencilBuffer(DepthStencilBufferPtr pTarget, 
																	CLEAR_DS_FLAG flag,
																	float d, 
																	int s)											= 0; 

		virtual void									Present()													= 0;

		virtual GPUBufferPtr							CreateBuffer(BUFFER_TYPE type, 
																	int bytes, 
																	void* pInitData, 
																	bool dynamic)									= 0;

		virtual void									VSSetConstantBuffer(GPUBufferPtr pBuffer)					= 0;
		virtual void									PSSetConstantBuffer(GPUBufferPtr pBuffer)					= 0;

		virtual void									SetIndexBuffer(GPUBufferPtr pBuffer, G_FORMAT type)			= 0;
		virtual void									SetVertexBuffer(GPUBufferPtr pBuffer, 
																	unsigned int offset, 
																	unsigned int stride)							= 0;

		virtual MaterialPtr								CreateMaterialFromFile(const char* szFile)						= 0;
		
		virtual TexturePtr								CreateTextureFromFile(const char* szFile)					= 0;

		virtual void									SetRenderTarget(RenderTargetPtr pRenderTarget)				= 0;

		virtual void									SetRenderTarget(MultiRenderTargetPtr pRT)					= 0;

		virtual RenderTargetPtr							CreateRenderTarget(int w, 
																	int h, 
																	G_FORMAT format, 
																	int miplvls = 1)								= 0;

		virtual MultiRenderTargetPtr					CreateMultiRenderTarget(int count,
																	int w,
																	int h,
																	G_FORMAT formats[],
																	int miplvls = 1)								= 0;
		virtual DepthStencilBufferPtr					CreateDepthStencilBuffer(int w, 
																	int h, 
																	G_FORMAT format)								= 0;

		virtual void									ResizeFrameBuffer(int cx, int cy)							= 0;

	protected:
		Sys_Graphics(void){}
		virtual ~Sys_Graphics(void){}
	};


}
