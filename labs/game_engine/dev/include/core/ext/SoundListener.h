#pragma once

#include "core\GameObjectComponent.h"
namespace ld3d
{

	class SoundListener : public GameObjectComponent
	{
	public:
		SoundListener(GameObjectManagerPtr pManager);
		virtual ~SoundListener(void);

		void										Update();
		
		bool										OnSerialize(DataStream* pStream);
		bool										OnUnSerialize(DataStream* pStream, const Version& version );
		const Version&								GetVersion() const;

	private:
		bool										OnAttach();
		void										OnDetach();
	};



}
