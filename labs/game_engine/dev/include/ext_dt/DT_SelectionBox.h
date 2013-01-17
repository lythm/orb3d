#pragma once

#include "core\GameObjectComponent.h"
namespace ld3d
{
	class DT_SelectionBox : public GameObjectComponent
	{
	public:
		class BoxRenderData: public RenderData
		{
		public:
			void											Render_Depth(Sys_GraphicsPtr pSysGraphics);
			void											Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial = MaterialPtr());
			MaterialPtr										GetMaterial();
			math::Matrix44									GetWorldMatrix();
			bool											IsDeferred(){return false;}
		};


		DT_SelectionBox(GameObjectManagerPtr pManager);
		virtual ~DT_SelectionBox(void);

		void										Update();
		const Version&								GetVersion() const;
	private:
		bool										OnAttach();
		void										OnDetach();
	};


}