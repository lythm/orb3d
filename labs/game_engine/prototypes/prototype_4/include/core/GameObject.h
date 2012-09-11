#pragma once

#include "core\Node.h"

namespace engine
{
	class EXPORT_CLASS GameObject : public Node
	{
	public:
		GameObject(void);
		virtual ~GameObject(void);


		void										Update();
		
		void										AddComponent(GameObjectComponentPtr pCom);


		GameObjectComponentPtr						GetComponent(const char* szName);

		GameObjectPtr								ThisPtr();
	private:
		void										UpdateComponents();

	private:
		std::vector<GameObjectComponentPtr>			m_components;

	};
}
