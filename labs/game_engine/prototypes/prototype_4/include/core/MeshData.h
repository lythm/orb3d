#pragma once

#include "core\GameObjectComponent.h"


namespace engine
{
	namespace object_component
	{
		class EXPORT_CLASS MeshData : public GameObjectComponent
		{
		public:
			MeshData();
			virtual ~MeshData(void);


			void						Update();
			MeshPtr						GetMesh();
			void						SetMesh(MeshPtr pMesh);
			bool						OnAttach();
			void						OnDetach();

			bool						LoadMesh();

			static MeshDataPtr			CreateComponent();
		private:
			void						ResetMeshRenderer();
		private:
			MeshPtr						m_pMesh;
		};
	}
}
