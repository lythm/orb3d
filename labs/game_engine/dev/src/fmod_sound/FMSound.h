#pragma once

#include "core\Sys_Sound.h"

namespace ld3d
{
	class FMSound : public Sys_Sound
	{
	public:
		FMSound(void);
		virtual ~FMSound(void);

		bool								Initialize();
		void								Release();
	};


}