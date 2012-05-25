#pragma once


namespace engine
{
	class Mesh
	{
	public:
		Mesh(void);
		virtual ~Mesh(void);


		virtual unsigned int										GetRenderDataCount();
		virtual RenderDataPtr										GetRenderData(unsigned int index);

	private:

	};


}
