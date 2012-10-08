#pragma once

namespace engine
{
	class EXPORT_CLASS GFX
	{
	public:
		GFX(void){}
		virtual ~GFX(void){}


		virtual bool								BeginPass()								= 0;
		virtual void								EndPass()								= 0;
		virtual void								ApplyPass()								= 0;
		virtual bool								NextPass()								= 0;

		virtual void								Release()								= 0;

	};


}
