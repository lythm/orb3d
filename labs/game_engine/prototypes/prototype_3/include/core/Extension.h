#pragma once


namespace engine
{
	class GameObjectComponent;

	class Extension
	{
	public:

		virtual GameObjectComponent*					CreateComponent(const char* szName)					= 0;
		virtual void									DestroyComponent(GameObjectComponent* pCom)			= 0;


	protected:
		Extension(void){}

		virtual ~Extension(void){}
	};


}