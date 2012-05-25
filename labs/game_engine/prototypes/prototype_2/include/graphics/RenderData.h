#pragma once


namespace engine
{
	struct RenderData
	{
		enum PRIMITIVE
		{
			PRIMITIVE_TRIANGLELIST,

		};


		PRIMITIVE											m_primitive;

		GraphicsFXPtr										m_pGFX;

		GeometryBufferPtr									m_pGeometry;

	};
}
