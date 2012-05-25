#pragma once


#include "input\InputParameters.h"


namespace engine
{
	class Sys_Input
	{
	public:
		virtual bool										Initialize(const InputParameters& param)				= 0;
		virtual void										Release()												= 0;

	protected:
		Sys_Input(void){}
		virtual ~Sys_Input(void){}

		
	private:

	};
}
