#pragma once


#include "core\VertexFormat.h"

namespace ld3d
{
	class EXPORT_CLASS Material
	{
	public:
		Material(void){}
		virtual ~Material(void){}

		virtual int									FindPass(const std::string& name)							= 0;
		virtual void								ApplyVertexFormat()											= 0;

		virtual bool								Begin(int& nPass)											= 0;
		virtual void								End()														= 0;
		virtual void								ApplyPass(int index)										= 0;
		
		virtual bool								SetVertexFormat(const VertexFormat& format)					= 0;
		virtual void								Release()													= 0;

		virtual void								SetCBByName(const char* szName, void* buffer, int size)		= 0;
		virtual void								SetMatrixByName(const char* szParam, 
																const math::Matrix44& mat)						= 0;
		

		virtual void								SetTextureByName(const char* szName, 
																TexturePtr pTex)								= 0;

		virtual void								SetVectorByName(const char* szName,
																const math::Vector3& v)							= 0;

		virtual void								SetVectorByName(const char* szName,
																const math::Vector4& v)							= 0;

		virtual void								SetVectorByName(const char* szName,
																const math::Vector2& v)							= 0;

		virtual void								SetFloatByName(const char* szName, 
																float v)										= 0;

		virtual void								SetIntByName(const char* szName,
																int v)											= 0; 
		virtual void								SetCBBySemantic(const char* szName, GPUBufferPtr pCB)			= 0;
		virtual void								SetMatrixBySemantic(const char* szSemantic, 
																const math::Matrix44& mat)						= 0;
		virtual void								SetTextureBySemantic(const char* szName, 
																TexturePtr pTex)								= 0;
		virtual void								SetVectorBySemantic(const char* szName, 
																const math::Vector3& v)							= 0;
		virtual void								SetVectorBySemantic(const char* szName, 
																const math::Vector4& v)							= 0;
		virtual void								SetVectorBySemantic(const char* szName, 
																const math::Vector2& v)							= 0;
		virtual void								SetFloatBySemantic(const char* szName, 
																float v)										= 0;
		virtual void								SetIntBySemantic(const char* szName, 
																int v)											= 0;

		virtual bool								SelectTechByName(const char* szName)						= 0;

		virtual void								SetViewMatrix(const math::Matrix44& val)					= 0;
		virtual void								SetProjMatrix(const math::Matrix44& val)					= 0;
		virtual void								SetWorldMatrix(const math::Matrix44& val)					= 0;
		virtual void								SetGBuffer(RenderTargetPtr pGBuffer)					= 0;
		virtual void								SetABuffer(RenderTargetPtr pABuffer)						= 0;
	};
}
