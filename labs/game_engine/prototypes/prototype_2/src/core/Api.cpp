#include "core_pch.h"
#include "..\..\include\core\Api.h"
#include "core\EngineCore.h"

namespace engine
{

	boost::shared_ptr<EngineCore>
		EngineCreate(const EngineParameters& param)
	{

		boost::shared_ptr<EngineCore> ptr = boost::shared_ptr<EngineCore>(new EngineCore);

		if(ptr == NULL)
		{
			return boost::shared_ptr<EngineCore>();
		}

		if(false == ptr->Initialize(param))
		{
			return boost::shared_ptr<EngineCore>();
		}
		return ptr;
	}

	namespace debug
	{
		void Trace(const std::string msg)
		{
			OutputDebugStringA(msg.c_str());
			OutputDebugStringA("\n");
		}
	}
}
