#include "StdAfx.h"
#include "GridMesh.h"
//#include "AppContext.h"


GridMesh::GridMesh(void)
{
}


GridMesh::~GridMesh(void)
{
}
bool GridMesh::Init(ld3d::CoreApiPtr pCore, int size, int grid_size)
{
	using namespace ld3d;

	m_pCore = pCore;
	m_size = size;
	m_gridSize = grid_size;
	
	Sys_GraphicsPtr pGraphics =pCore->GetSysGraphics();
	
	m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * ((size / grid_size + 1) * 4), NULL, true);

	math::Vector3* pBuffer = (math::Vector3*)m_pVB->Map(MAP_DISCARD);

	math::Vector3* pBufferData = pBuffer;

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = size/2;
	}

	pBuffer += (size / grid_size + 1);
	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = -size/2;
	}
	pBuffer += (size / grid_size + 1);



	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}
	pBuffer += (size / grid_size + 1);


	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}
		
	m_pVB->Unmap();


	int line_count = (size / grid_size + 1) + (size / grid_size + 1) ;
	int index_count = line_count * 2;
	m_pIB = pGraphics->CreateBuffer(BT_INDEX_BUFFER, index_count * sizeof(int), NULL, true);

	int * pIB = (int*)m_pIB->Map(MAP_DISCARD);

	int * pData = pIB;

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		*(pIB + 2* i) = i;
		*(pIB + 2* i + 1) = i + size / grid_size + 1;
	}

	pIB += 2 * (size / grid_size + 1);
	for(int i = 0; i < (size / grid_size + 1) ; ++i)
	{
		*(pIB + 2* i) = i + 2 * (size / grid_size + 1);
		*(pIB + 2* i + 1) = i + size / grid_size + 1 + 2 * (size / grid_size + 1);
	}
	
	m_pIB->Unmap();

	m_pMaterial = pGraphics->CreateMaterialFromFile("./assets/standard/material/editor_grid.fx");


	
	VertexFormat format;
	format.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));

	m_pMaterial->SetVertexFormat(format);

	return true;
}
void GridMesh::Release()
{
	m_pIB->Release();
	m_pVB->Release();
	m_pMaterial->Release();
}

void GridMesh::Render(ld3d::Sys_GraphicsPtr pGraphics, ld3d::MaterialPtr pMaterial)
{
	using namespace ld3d;

	using namespace math;

	int size = m_size;
	int grid_size = m_gridSize;

	int line_count = (size / grid_size + 1) + (size / grid_size + 1) ;
	int index_count = line_count * 2;

	pGraphics->SetIndexBuffer(m_pIB, G_FORMAT_R32_UINT);
	pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
	pGraphics->SetPrimitiveType(PT_LINE_LIST);

	m_pMaterial->ApplyVertexFormat();
	
	int nPass = 0;

	m_pMaterial->Begin(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pMaterial->ApplyPass(i);

		pGraphics->DrawIndexed(index_count, 0, 0);
	}

	m_pMaterial->End();

}
ld3d::MaterialPtr GridMesh::GetMaterial()
{
	return m_pMaterial;
}
math::Matrix44 GridMesh::GetWorldMatrix()
{
	math::Matrix44 mat;
	mat.MakeIdentity();
	return mat;
	
}
void GridMesh::Render_Depth(ld3d::Sys_GraphicsPtr pSysGraphics)
{
}
bool GridMesh::IsDeferred()
{
	return false;
}

