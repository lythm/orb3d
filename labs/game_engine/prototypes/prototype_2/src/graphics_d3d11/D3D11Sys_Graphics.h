#pragma once

#include "graphics\Sys_Graphics.h"


#include "graphics\RenderData.h"


namespace engine
{
	class D3D11Sys_Graphics : public Sys_Graphics
	{
	public:
		D3D11Sys_Graphics(void);
		virtual ~D3D11Sys_Graphics(void);

		bool									Initialize(const GraphicsParameters& param);
		void									Release();

		void									ClearRenderTarget();

		void									Present();

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);

		void									PushRenderData(RenderDataPtr pData);

		void									Render();

		void									SetRenderTarget(RenderTargetPtr pTarget);


		GeometryBufferPtr						CreateGeometryBuffer();
		GraphicsFXPtr							CreateGFX();

		FrameBufferPtr							GetFrameBuffer();
		
	private:

		void									Render(const RenderData& data);

	private:

		ID3D11Device*							m_pDevice;

		ID3D11DeviceContext*					m_pContext;
	
		FrameBufferPtr							m_pFrameBuffer;


	private:

		RenderData								m_renderData;

		
	};
}
