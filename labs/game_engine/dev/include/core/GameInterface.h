#pragma once


namespace ld3d
{
	class GameInterface
	{
	protected:

		GameInterface(void){}

		virtual ~GameInterface(void){}

	public:

		virtual bool									Initialize(CoreApiPtr pCore)								= 0;
		virtual void									Release()													= 0;
		virtual bool									Update()													= 0;
	};


}