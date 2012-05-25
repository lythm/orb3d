#pragma once

#include "graphics\SysGraphics.h"

#include "RenderQueue.h"

#include <Cg\cgD3D11.h>

namespace engine
{
	class D3D11SysGraphics : public SysGraphics
	{
	public:
		D3D11SysGraphics(void);
		virtual ~D3D11SysGraphics(void);

		bool									Initialize(const SysGraphicsParameters& param);

		void									Release();
		void									Draw(RenderDataPtr pData);
		void									PushRenderData(RenderDataPtr pData);
		void									ClearRenderQueue();
		void									Render();
		
		void									SetViewTransform(const math::Matrix44& view);
		void									SetProjTransform(const math::Matrix44& proj);

		void									SetClearColor(const math::Color4& clr);
		void									SetClearDepth(float d);
		void									SetClearStencil(uint32 val);
		void									ClearRenderTarget();
		void									SetRenderTarget(Texture2DPtr pTarget);
		void									Present();

		RenderDataPtr							CreateRenderData();
		Texture2DPtr							CreateTexture2D();
		TexturePtr								CreateRenderTarget();

		ShaderPtr								CreateShader();
	private:
		RenderQueue								m_queue;

		ID3D11Device*							m_pDevice;

		ID3D11DeviceContext*					m_pContext;

		IDXGISwapChain*							m_pSwapChain;

		ID3D11RenderTargetView*					m_pFrameBuffer;
		ID3D11DepthStencilView*					m_pDepthStencilBuffer;

		math::Color4							m_clearColor;
		float									m_clearDepth;
		int										m_clearStencil;


		 CGcontext								m_pCG;
		
	};


}