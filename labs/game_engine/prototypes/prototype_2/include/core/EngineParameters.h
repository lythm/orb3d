#pragma once


#include <graphics/GraphicsParameters.h>
#include <input/InputParameters.h>


namespace engine
{
	class EngineParameters
	{
	public:

		GraphicsParameters						graphics;

		InputParameters							input;
		
	};
}