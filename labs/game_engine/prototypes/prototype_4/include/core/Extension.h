#pragma once

namespace engine
{
	class Extension
	{
	public:


		virtual int									GetComponentCount()						= 0;


	protected:

		Extension(void){}
		virtual ~Extension(void){}
	};


}
