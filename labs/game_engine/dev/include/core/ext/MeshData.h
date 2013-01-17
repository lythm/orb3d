#pragma once

#include "core\GameObjectComponent.h"

namespace ld3d
{
	class EXPORT_CLASS MeshData : public GameObjectComponent
	{
	public:
		MeshData(GameObjectManagerPtr pManager);
		virtual ~MeshData(void);


		void						Update();
		MeshPtr						GetMesh();
		void						SetMesh(MeshPtr pMesh);
		bool						OnAttach();
		void						OnDetach();

		void						SetMeshAsset(const std::wstring& asset);
		const std::wstring&			GetMeshAsset();


		bool						OnSerialize(DataStream* pStream);
		bool						OnUnSerialize(DataStream* pStream, const Version& version );

		const Version& 				GetVersion() const;
	private:
		bool						LoadMesh(const std::wstring& asset);
		void						ResetMeshRenderer();
	private:
		MeshPtr						m_pMesh;

		std::wstring				m_meshAsset;
	};
}
