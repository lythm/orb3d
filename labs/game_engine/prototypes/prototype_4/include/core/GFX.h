#pragma once


#include "core\VertexFormat.h"

namespace engine
{
	class EXPORT_CLASS GFX
	{
	public:
		GFX(void){}
		virtual ~GFX(void){}

		virtual int									FindPass(const std::string& name)							= 0;
		virtual void								ApplyVertexFormat()											= 0;

		virtual bool								BeginPass(int& nPass)										= 0;
		virtual void								EndPass()													= 0;
		virtual void								ApplyPass(int index)										= 0;
		
		virtual bool								SetVertexFormat(VertexElement format[], 
																uint32 nElem)									= 0;
		virtual void								Release()													= 0;

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
	};


}
