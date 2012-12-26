#pragma once

#include "core\GameObjectComponent.h"

namespace engine
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

		void						SetMeshAsset(const std::wstring& asset);
		const std::wstring&			GetMeshAsset();

	private:
		void						ResetMeshRenderer();
	private:
		MeshPtr						m_pMesh;

		std::wstring				m_meshAsset;
	};
}
