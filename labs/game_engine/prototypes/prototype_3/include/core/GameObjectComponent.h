#pragma once


namespace engine
{
	class GameObject;
	class GameObjectComponent 
	{
	public:
		
		virtual void						AttachToObject(GameObject* pObject)										= 0;

	
	protected:
		GameObjectComponent(void){m_pObject = NULL;}
		virtual ~GameObjectComponent(void){}


	private:
		GameObject*							m_pObject;

	};
}
