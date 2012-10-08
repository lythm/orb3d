#include "ogl4graphics_pch.h"
#include "OGL4Graphics.h"




EXPORT_C_API engine::Sys_Graphics* CreateSys()
{
	//return new engine::OGL4Graphics;

	return NULL;
}

EXPORT_C_API void DestroySys(engine::Sys_Graphics* pSys)
{
	delete (engine::OGL4Graphics*)pSys;
}

namespace engine
{
	OGL4Graphics::OGL4Graphics(void)
	{
	}


	OGL4Graphics::~OGL4Graphics(void)
	{
	}
	bool OGL4Graphics::Initialize(void* app_handle, uint32 width, uint32 height)
	{
		return true;
	}
	void OGL4Graphics::Release()
	{
	}

	void OGL4Graphics::Draw(RenderDataPtr pData)
	{
	}
	void OGL4Graphics::Render()
	{
	}

	void OGL4Graphics::SetViewTransform(const math::Matrix44& view)
	{
	}
	void OGL4Graphics::SetProjTransform(const math::Matrix44& proj)
	{
	}

	void OGL4Graphics::SetClearColor(const math::Color4& clr)
	{
	}
	void OGL4Graphics::SetClearDepth(float d)
	{
	}
	void OGL4Graphics::SetClearStencil(uint32 val)
	{
	}

	void OGL4Graphics::ClearRenderTarget()
	{
	}

	void OGL4Graphics::Present()
	{
	}


	void OGL4Graphics::SetIndexBuffer(GPUBufferPtr pBuffer)
	{
	}
	void OGL4Graphics::SetVertexBuffer(GPUBufferPtr pBuffer)
	{
	}

	GPUBufferPtr OGL4Graphics::CreateBuffer(BUFFER_TYPE type, int bytes, void* pInitData, bool dynamic)
	{
		return GPUBufferPtr();
	}
	GFXPtr OGL4Graphics::CreateGFXFromFile(const char* szFile)
	{
		return GFXPtr();
	}
}
