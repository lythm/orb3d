#include "core_pch.h"
#include "..\..\include\core\MeshUtil.h"
#include "core\Mesh.h"
#include "core\Material.h"
#include "core\VertexFormat.h"
#include "core\SubMesh.h"
#include "core_utils.h"
#include "core\Sys_Graphics.h"
#include "core\GPUBuffer.h"

namespace ld3d
{
	MeshUtil::MeshUtil(void)
	{
	}


	MeshUtil::~MeshUtil(void)
	{
	}
	MeshPtr MeshUtil::CreateCone(float range, float angle, float slice, MaterialPtr pMat)
	{
		MeshPtr pMesh = alloc_object<Mesh>();

		VertexFormat format;
		format.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		format.AddElement(VertexElement(0, VertexElement::NORMAL, G_FORMAT_R32G32B32_FLOAT));

		pMat->SetVertexFormat(format);

		float radius = tanf(math::D2R(angle)) * range;
		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		int nVerts = slice * 6;
		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * nVerts);

		int n = 0;
		for(int i = 0; i < slice; i++)
		{
			float th = 360.0f / float(slice) * i;
			// side
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;

			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();
			
			n++;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;
			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();
			n++ ;


			pVerts[n].pos.x = 0;
			pVerts[n].pos.z = 0;
			pVerts[n].pos.y = range;
			pVerts[n].normal = pVerts[n].pos;
			pVerts[n].normal.Normalize();
			n++ ;

			// bottom
			th = 360.0f / float(slice) * i;
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;

			pVerts[n].normal = math::Vector3(0, 0, -1);
			
			n++;

			pVerts[n].pos.x = 0;
			pVerts[n].pos.z = 0;
			pVerts[n].pos.y = 0;
			pVerts[n].normal = math::Vector3(0, 0, -1);
			n++ ;
			
			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].pos.x = radius * sinf(math::D2R(th));
			pVerts[n].pos.z = radius * cosf(math::D2R(th));
			pVerts[n].pos.y = 0;
			pVerts[n].normal = math::Vector3(0, 0, -1);
			n++ ;
		}

		std::vector<MaterialPtr> mats;
		mats.push_back(pMat);

		if(false == pMesh->Create(0, nullptr, sizeof(Vertex) * nVerts, pVerts, mats))
		{
			mem_free(pVerts);
			return MeshPtr();
		}

		SubMeshPtr pSub = alloc_object<SubMesh>();

		pSub->Create(pMesh, 0, 0, 0, nVerts, sizeof(Vertex), 0, 2, PT_TRIANGLE_LIST, format, G_FORMAT_R16_UINT);
		pMesh->AddSubMesh(pSub);
		
		mem_free(pVerts);
		return pMesh;
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

		size = size / 2.0f;

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

		size = size / 2.0f;
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

		int NumVertices = 0;
		math::Vector3* pPos = CreateSphere(radius, slice, stack, NumVertices);
		
		struct Vertex
		{
			math::Vector3 pos;
			math::Vector3 normal;
		};

		Vertex* pVerts = (Vertex*)mem_alloc(sizeof(Vertex) * NumVertices);
		for(int i = 0; i < NumVertices; ++i)
		{
			pVerts[i].pos = pPos[i];
			pVerts[i].normal = pPos[i];
			pVerts[i].normal.Normalize();

		}
		
		mem_free(pPos);

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
	
	math::Vector3* MeshUtil::CreateSphere(float radius, float slice, float stack, int& nVerts)
	{
#define DTOR (3.14f / 180.f)
		int theta, phi; 

		int dtheta = int(360 / slice); 
		int dphi = int(180 / stack); 

		nVerts = (int) ((360/dtheta) * (180/dphi) * 4); 
		
		math::Vector3* pVerts = (math::Vector3*)mem_alloc(sizeof(math::Vector3) * nVerts);

		int n = 0; 

		for (phi = 0; phi <= 180 - dphi; phi += (int)dphi) 
		{ 
			for (theta = 0; theta <= 360 - dtheta; theta += (int)dtheta) 
			{ 
				math::Vector3 pos;
				pos.x = radius * sinf(phi * DTOR) * cosf(theta * DTOR); 
				pos.y = radius * sinf(phi * DTOR) * sinf(theta * DTOR); 
				pos.z = radius * cosf(phi * DTOR); 
				pVerts[n] = pos;
				n++; 

				pos.x = radius * sinf((phi + dphi) * DTOR) * cosf(theta * DTOR); 
				pos.y = radius * sinf((phi + dphi) * DTOR) * sinf(theta * DTOR); 
				pos.z = radius * cosf((phi + dphi) * DTOR); 
				pVerts[n] = pos;
				n++; 

				pos.x = radius * sinf(phi * DTOR) * cosf((theta + dtheta) * DTOR); 
				pos.y = radius * sinf(phi * DTOR) * sinf((theta + dtheta) * DTOR); 
				pos.z = radius * cosf(phi * DTOR); 
				pVerts[n] = pos;
				n++; 

				if (phi > -180 && phi < 180) 
				{ 
					pos.x = radius * sinf((phi + dphi) * DTOR) * cosf((theta + dtheta) * DTOR); 
					pos.y = radius * sinf((phi + dphi) * DTOR) * sinf((theta + dtheta) * DTOR); 
					pos.z = radius * cosf((phi + dphi) * DTOR); 
					pVerts[n] = pos;
					n++; 
				} 
			} 
		}
		
		return pVerts;
	}
	math::Vector3* MeshUtil::CreateSpotLightCone(float range, float angle, float slice, int& nVerts)
	{
		float radius = tanf(math::D2R(angle)) * range;
		
	
		nVerts = slice * 6;
		math::Vector3* pVerts = (math::Vector3*)mem_alloc(sizeof(math::Vector3) * nVerts);

		int n = 0;
		for(int i = 0; i < slice; i++)
		{
			float th = 360.0f / float(slice) * i;
			// side
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++;

			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++ ;


			pVerts[n].x = 0;
			pVerts[n].z = 0;
			pVerts[n].y = 0;
			n++ ;

			// bottom
			th = 360.0f / float(slice) * i;
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++;

			pVerts[n].x = 0;
			pVerts[n].z = range;
			pVerts[n].y = 0;
			n++ ;
			
			th = 360.0f / float(slice) * (i + 1);
			pVerts[n].x = radius * sinf(math::D2R(th));
			pVerts[n].z = range;
			pVerts[n].y = radius * cosf(math::D2R(th));
			n++ ;
		}

		return pVerts;
	}
}
