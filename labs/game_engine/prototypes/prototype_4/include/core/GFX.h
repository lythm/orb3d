#pragma once


#include "core\VertexFormat.h"

namespace engine
{
	class EXPORT_CLASS GFX
	{
	public:
		GFX(void){}
		virtual ~GFX(void){}


		virtual bool								BeginPass()								= 0;
		virtual void								EndPass()								= 0;
		virtual void								ApplyPass()								= 0;
		
		virtual bool								SetVertexFormat(VertexElement format[], 
																uint32 nElem)				= 0;
		virtual void								Release()								= 0;

		virtual void								SetMatrixByName(const char* szParam, 
																const math::Matrix44& mat)	= 0;

	};


}
