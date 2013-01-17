#pragma once

namespace ld3d
{
	class DT_Gizmo : public GameObjectComponent
	{
	public:
		enum OP_MODE
		{
			OPM_MOVE,
			OPM_ROTATE,
			OPM_SCALE,
		};

		enum GIZMO_STATE
		{
			g_state_active,
			g_state_inactive,

		};

		DT_Gizmo(GameObjectManagerPtr pManager);
		virtual ~DT_Gizmo(void);

		void											Update();
		void											ChangeMode(OP_MODE mode);
		OP_MODE											GetMode();

		const Version&									GetVersion() const;

	private:
		GIZMO_STATE										m_state;
		OP_MODE											m_mode;
	};
}
