#pragma once

namespace engine
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
		DT_Gizmo(GameObjectManagerPtr pManager);
		virtual ~DT_Gizmo(void);

		void											Update();
		void											ChangeMode(OP_MODE mode);
		OP_MODE											GetMode();
	private:

		OP_MODE											m_mode;
	};
}
