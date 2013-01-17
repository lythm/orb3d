#include "gameeditor_ext_pch.h"
#include "ext_dt\DT_SelectionBox.h"

namespace ld3d
{
	DT_SelectionBox::DT_SelectionBox(GameObjectManagerPtr pManager) : GameObjectComponent(L"DT_SelectionBox", pManager)
	{
	}


	DT_SelectionBox::~DT_SelectionBox(void)
	{
	}
	void DT_SelectionBox::Update()
	{
	}

	bool DT_SelectionBox::OnAttach()
	{
	
		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"DT_SelectionBox");
		{
		}
		pPM->End();

		return true;
	}
	void DT_SelectionBox::OnDetach()
	{
	}
	const Version& DT_SelectionBox::GetVersion() const
	{
		return g_packageVersion;
	}
	void DT_SelectionBox::BoxRenderData::Render_Depth(Sys_GraphicsPtr pSysGraphics)
	{
	}
	void DT_SelectionBox::BoxRenderData::Render(Sys_GraphicsPtr pSysGraphics, MaterialPtr pMaterial)
	{
	}
	MaterialPtr DT_SelectionBox::BoxRenderData::GetMaterial()
	{
		return MaterialPtr();
	}
	math::Matrix44 DT_SelectionBox::BoxRenderData::GetWorldMatrix()
	{
		return math::MatrixIdentity();
	}
}
