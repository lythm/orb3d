#include "gameeditor_ext_pch.h"
#include "..\..\include\ext_dt\DT_Gizmo.h"


namespace ld3d
{
	DT_Gizmo::DT_Gizmo(GameObjectManagerPtr pManager) : GameObjectComponent(L"DT_Gizmo", pManager)
	{
		m_mode = OPM_MOVE;
	}


	DT_Gizmo::~DT_Gizmo(void)
	{
	}
	void DT_Gizmo::ChangeMode(OP_MODE mode)
	{
		m_mode = mode;
	}
	DT_Gizmo::OP_MODE DT_Gizmo::GetMode()
	{
		return m_mode;
	}
	void DT_Gizmo::Update()
	{
	}
	const Version& DT_Gizmo::GetVersion() const
	{
		return g_packageVersion;
	}
}
