#include "core_pch.h"
#include "..\..\include\core\MeshData.h"

namespace engine
{
	namespace object_component
	{
		MeshData::MeshData(MeshPtr pMesh) : GameObjectComponent(L"MeshData")
		{
			m_pMesh = pMesh;
		}


		MeshData::~MeshData(void)
		{
		}
		void MeshData::Update()
		{

		}
		MeshPtr	MeshData::GetMesh()
		{
			return m_pMesh;
		}
	}
}
