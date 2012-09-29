#pragma once

namespace engine
{
	class GPUBuffer
	{
	public:

		enum MAP_HINT
		{
			MAP_DEFAULT,
			MAP_DISCARD,
			MAP_NO_OVERWRITE,

		};

		GPUBuffer(void){}

		virtual ~GPUBuffer(void){}

		virtual void*											Map(MAP_HINT hint)									= 0;
		virtual void											Unmap()												= 0;

		virtual void											Release()											= 0;


	};


}