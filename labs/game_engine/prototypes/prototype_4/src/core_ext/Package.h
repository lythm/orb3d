#pragma once

#include "core\ExtPackage.h"

namespace engine
{
	class Package : public ExtPackage
	{
	public:
		Package(CoreApiPtr pCore);
		virtual ~Package(void);

		std::wstring						GetPackageName();
		bool								RegisterPacket(GameObjectManager* pManager);

		static CoreApiPtr					GetCoreApi();

		static Allocator*					GetAllocator();
	private:
		static CoreApiPtr					s_pCore;
	};
}
