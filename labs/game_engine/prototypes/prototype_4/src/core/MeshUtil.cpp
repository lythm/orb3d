#include "core_pch.h"
#include "..\..\include\core\MeshUtil.h"
#include "core\Mesh.h"
#include "core\Material.h"
#include "core\VertexFormat.h"
#include "core\SubMesh.h"


namespace engine
{
	MeshUtil::MeshUtil(void)
	{
	}


	MeshUtil::~MeshUtil(void)
	{
	}
	MeshPtr MeshUtil::CreateSphere(float radius, float slice, float stack, MaterialPtr pMat)
	{
		MeshPtr pMesh = MeshPtr(new Mesh);

		VertexElement ve[] = 
		{
			VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32A32_FLOAT),
			VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32A32_FLOAT),
		};

		pMat->SetVertexFormat(ve, 2);

#define DTOR (3.14f / 180.f)
		int theta, phi; 

		int dtheta = 360 / slice; 
		int dphi = 180 / stack; 

		int NumVertices = (int) ((360/dtheta) * (180/dphi) * 4); 

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex* pVerts = new Vertex[NumVertices];

		int n = 0; 

		for (phi = 0; phi <= 180 - dphi; phi += (int)dphi) 
		{ 
			for (theta = 0; theta <= 360 - dtheta; theta += (int)dtheta) 
			{ 
				math::Vector3 pos;
				pos.x = radius * sinf(phi * DTOR) * cosf(theta * DTOR); 

				pos.y = radius * sinf(phi * DTOR) * sinf(theta * DTOR); 

				pos.z = radius * cosf(phi * DTOR); 

				pVerts[n].pos = pos;
				pVerts[n].normal = pos;
				pVerts[n].normal.Normalize();

				n++; 

				pos.x = radius * sinf((phi + dphi) * DTOR) * cosf(theta * DTOR); 

				pos.y = radius * sinf((phi + dphi) * DTOR) * sinf(theta * DTOR); 

				pos.z = radius * cosf((phi + dphi) * DTOR); 

				pVerts[n].pos = pos;
				pVerts[n].normal = pos;
				pVerts[n].normal.Normalize();

				n++; 

				pos.x = radius * sinf(phi * DTOR) * cosf((theta + dtheta) * DTOR); 

				pos.y = radius * sinf(phi * DTOR) * sinf((theta + dtheta) * DTOR); 

				pos.z = radius * cosf(phi * DTOR); 

				pVerts[n].pos = pos;
				pVerts[n].normal = pos;
				pVerts[n].normal.Normalize();

				n++; 

				if (phi > -180 && phi < 180) 
				{ 

					pos.x = radius * sinf((phi + dphi) * DTOR) * cosf((theta + dtheta) * DTOR); 

					pos.y = radius * sinf((phi + dphi) * DTOR) * sinf((theta + dtheta) * DTOR); 

					pos.z = radius * cosf((phi + dphi) * DTOR); 

					pVerts[n].pos = pos;
					pVerts[n].normal = pos;
					pVerts[n].normal.Normalize();
					n++; 
				} 
			} 
		}
		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, NULL, sizeof(Vertex) * NumVertices, pVerts, mats))
		{
			delete[] pVerts;
			return MeshPtr();
		}
		delete [] pVerts;

		SubMeshPtr pSub = SubMeshPtr(new SubMesh);

		pSub->Create(pMesh, 0, 0, 0, NumVertices, sizeof(Vertex), 0, NumVertices - 2, PT_TRIANGLE_STRIP);

		pMesh->AddSubMesh(pSub);

		return pMesh;
	}
}
