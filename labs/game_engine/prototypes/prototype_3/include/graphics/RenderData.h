#pragma once


#include "math\math_all.h"

namespace engine
{
	class RenderData
	{
	public:

		enum MAP_HINT
		{
			MAP_DEFAULT,
			MAP_DISCARD,
			MAP_NO_OVERWRITE,

		};


		virtual void										Release()													= 0;

		virtual bool										AllocIndexBuffer(unsigned int bytes, 
																void* pInitData, 
																bool dynamic)											= 0;
		
		virtual void*										MapVertexBuffer(MAP_HINT hint)								= 0;
		virtual void										UnmapVertexBuffer()											= 0;

		virtual void*										MapIndexBuffer(MAP_HINT hint)								= 0;
		virtual void										UnmapIndexBuffer()											= 0;

		virtual bool										AllocVertexBuffer(unsigned int bytes, 
																void* pInitData, 
																bool dynamic)											= 0;
		

		virtual void										SetTransform(const math::Matrix44& transform)				= 0;
		
		
		virtual void										SetShader(ShaderPtr pShader)								= 0;
	protected:
		RenderData(void){}

		virtual ~RenderData(void){}
	};
}
