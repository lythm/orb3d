#pragma once


namespace engine
{

	class EXPORT_CLASS RenderData
	{
	public:
		RenderData(void);
		virtual ~RenderData(void);



		void										SetTransform(const math::Matrix44& tf);
		
		void										UpdateVertexBuffer(void* buffer, int bytes);
		void										UpdateIndexBuffer(void* buffer, int bytes);
		
		void										SetGFX(GFXPtr pGFX);


	private:


	};


}
