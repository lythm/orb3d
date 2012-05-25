#pragma once

#include "graphics\FrameBuffer.h"

#include "graphics\GraphicsParameters.h"

namespace engine
{
	class D3D11FrameBuffer : public FrameBuffer
	{
	public:
		D3D11FrameBuffer(void);
		virtual ~D3D11FrameBuffer(void);

		bool									Initialize(ID3D11Device* pDevice, const GraphicsParameters& param);
		void									Release();


		void									ClearColor();
		void									ClearDepthStencil();
		void									SetClearColor(const math::Color4& clr);
		void									SetDepthStencil(float depth, uint32 stencil);

		void									Present();

		RenderTargetPtr							GetRenderTarget();

	private:
		ID3D11Device*							m_pDevice;
		
		IDXGISwapChain*							m_pSwapChain;

		ID3D11DeviceContext*					m_pContext;

		math::Color4							m_clearColor;
		float									m_clearDepth;
		int										m_clearStencil;

		RenderTargetPtr							m_pRenderTarget;
	};
}