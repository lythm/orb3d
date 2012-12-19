#pragma once

namespace engine
{
	class ExtPackage
	{
	public:
		
		virtual std::wstring						GetPackageName()								= 0;
		virtual bool								RegisterPacket(GameObjectManager*	 pManager)	= 0;
		
	protected:
		ExtPackage(void){}
		virtual ~ExtPackage(void){}
	private:

	};


}