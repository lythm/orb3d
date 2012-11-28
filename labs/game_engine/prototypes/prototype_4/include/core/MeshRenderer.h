#pragma once

#include "core\GameObjectComponent.h"
#include "core\RenderData.h"


namespace engine
{
	namespace object_component
	{
		class EXPORT_CLASS MeshRenderer : public GameObjectComponent
		{
			class SubMeshRenderData : public RenderData
			{
				void											Render(Sys_GraphicsPtr pSysGraphics);
				GFXPtr											GetGFX();
				math::Matrix44									GetWorldMatrix();
			};
		public:
			MeshRenderer(RenderSystemPtr pRS);
			virtual ~MeshRenderer(void);

			void							Update();

		private:
			bool							OnAttach();
		private:

			RenderSystemPtr					m_pRS;
		};

	}
}
