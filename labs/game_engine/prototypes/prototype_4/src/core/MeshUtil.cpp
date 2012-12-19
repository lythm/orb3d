#include "core_pch.h"
#include "..\..\include\core\MeshUtil.h"
#include "core\Mesh.h"
#include "core\Material.h"
#include "core\VertexFormat.h"
#include "core\SubMesh.h"
#include "core_utils.h"

namespace engine
{
	MeshUtil::MeshUtil(void)
	{
	}


	MeshUtil::~MeshUtil(void)
	{
	}
	MeshPtr MeshUtil::CreatePlane(float size, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();

		VertexFormat format;
		format.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		format.AddElement(VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32_FLOAT));

		pMat->SetVertexFormat(format);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex pVerts[] = 
		{
			// front
			{math::Vector3(-size, 0, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(-size, 0, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, size), math::Vector3(0, 1, 0),},
			
			
			{math::Vector3(-size, 0, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, 0, -size), math::Vector3(0, 1, 0),},
		
		};

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, nullptr, sizeof(Vertex) * 6, pVerts, mats))
		{
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, 6, sizeof(Vertex), 0, 2, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);
		
		return pMesh;
	}
	MeshPtr MeshUtil::CreateCube(float size, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();


		VertexFormat format;
		format.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		format.AddElement(VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32_FLOAT));

		pMat->SetVertexFormat(format);

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex pVerts[] = 
		{
			// front
			{math::Vector3(-size, size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(size, size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(size, -size, -size), math::Vector3(0, 0, -1),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, 0, -1),},

			// back
			{math::Vector3(-size, size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(size, size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(size, -size, size), math::Vector3(0, 0, 1),},
			{math::Vector3(-size, -size, size), math::Vector3(0, 0, 1),},

			// top
			{math::Vector3(-size, size, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, size, size), math::Vector3(0, 1, 0),},
			{math::Vector3(size, size, -size), math::Vector3(0, 1, 0),},
			{math::Vector3(-size, size, -size), math::Vector3(0, 1, 0),},
			// bottom
			{math::Vector3(-size, -size, size), math::Vector3(0, -1, 0),},
			{math::Vector3(size, -size, size), math::Vector3(0, -1, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(0, -1, 0),},
			{math::Vector3(-size, -size, -size), math::Vector3(0, -1, 0),},

			// left
			{math::Vector3(-size, size, size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, size, -size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, -size, -size), math::Vector3(-1, 0, 0),},
			{math::Vector3(-size, -size, size), math::Vector3(-1, 0, 0),},
			// right
			{math::Vector3(size, size, size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, size, -size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, -size, -size), math::Vector3(1, 0, 0),},
			{math::Vector3(size, -size, size), math::Vector3(1, 0, 0),},
		};

		uint16 pIndice[] = 
		{
			// front
			0, 1, 2,
			0, 2, 3,

			// back
			4, 6, 5, 
			4, 7, 6,


			//top
			8, 9, 10,
			8, 10, 11,

			// bottom
			12, 14, 13,
			12, 15, 14,

			// left
			16, 17, 18,
			16, 18, 19,

			// right
			20, 22, 21,
			20, 23, 22,

		};
		

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(sizeof(uint16) * 36, pIndice, sizeof(Vertex) * 24, pVerts, mats))
		{
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 36, 0, 24, sizeof(Vertex), 0, 12, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);
		
		return pMesh;
	}
	MeshPtr MeshUtil::CreateSphere(float radius, float slice, float stack, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();

		
		VertexFormat format;
		format.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		format.AddElement(VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32_FLOAT));

		pMat->SetVertexFormat(format);

#define DTOR (3.14f / 180.f)
		int theta, phi; 

		int dtheta = int(360 / slice); 
		int dphi = int(180 / stack); 

		int NumVertices = (int) ((360/dtheta) * (180/dphi) * 4); 

		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * NumVertices);

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
			mem_free(pVerts);
			return MeshPtr();
		}
		mem_free(pVerts);

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, NumVertices, sizeof(Vertex), 0, NumVertices - 2, PT_TRIANGLE_STRIP, format, G_FORMAT_R16_UINT);

		pMesh->AddSubMesh(pSub);

		return pMesh;
	}
}
