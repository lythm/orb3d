#pragma once


namespace engine
{
	class RenderData
	{
	public:

		enum DR_STAGE
		{
			DR_GEOMETRY,
			DR_LIGHTING,
			DR_POSTEFFECT,
			DR_MERGE,
		};

		RenderData(void){}

		virtual ~RenderData(void){}

		virtual void											Render_Depth(Sys_GraphicsPtr pSysGraphics)									= 0;
		virtual void											Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr())	= 0;
		virtual MaterialPtr										GetMaterial()																= 0;
		virtual math::Matrix44									GetWorldMatrix()															= 0;
		virtual bool											IsDeferred(){return false;}

	};
}
