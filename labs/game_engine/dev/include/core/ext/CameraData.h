#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class CameraData : public GameObjectComponent
	{
	public:
		CameraData(GameObjectManagerPtr pManager);
		virtual ~CameraData(void);

		const Version&				GetVersion() const;

		bool						OnAttach();
		void						OnDetach();
		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version);

		void						Update();
	private:
		CameraPtr					m_pCamera;
	};


}
