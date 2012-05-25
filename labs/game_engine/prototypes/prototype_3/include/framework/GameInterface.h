#pragma once


namespace engine
{
	class GameInterface
	{
	protected:

		GameInterface(void){}

		virtual ~GameInterface(void){}

	public:

		virtual bool									Initialize(engine::GameEnginePtr pEngine)					= 0;
		virtual void									Release()													= 0;
		virtual bool									Update()													= 0;
	};


}