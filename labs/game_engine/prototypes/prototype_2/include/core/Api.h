#pragma once

#include "core/EngineParameters.h"


namespace engine
{

	class EngineCore;


	EXPORT_API boost::shared_ptr<EngineCore>					EngineCreate(const EngineParameters& param);


	namespace debug
	{
		EXPORT_API void											Trace(const std::string msg);
	}

}
