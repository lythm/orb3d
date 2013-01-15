#pragma once

namespace ld3d
{
	class GPUBuffer
	{
	public:

		GPUBuffer(void){}

		virtual ~GPUBuffer(void){}

		virtual void*											Map(MAP_HINT hint)									= 0;
		virtual void											Unmap()												= 0;

		virtual void											Release()											= 0;


	};


}