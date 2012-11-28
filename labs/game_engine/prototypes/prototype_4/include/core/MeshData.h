#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{
	namespace object_component
	{
		class EXPORT_CLASS MeshData : public GameObjectComponent
		{
		public:
			MeshData(MeshPtr pMesh);
			virtual ~MeshData(void);


			void						Update();

			MeshPtr						GetMesh();
		private:
			MeshPtr						m_pMesh;
		};


	}
}