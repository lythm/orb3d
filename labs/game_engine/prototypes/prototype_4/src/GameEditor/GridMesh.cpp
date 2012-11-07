#include "StdAfx.h"
#include "GridMesh.h"
#include "AppContext.h"


GridMesh::GridMesh(void)
{
}


GridMesh::~GridMesh(void)
{
}
bool GridMesh::Init()
{
	using namespace engine;

	int size = 100;
	int grid_size = 10;
	

	
	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();

	

	m_pVB = pGraphics->CreateBuffer(BT_VERTEX_BUFFER, sizeof(math::Vector3) * ((size / grid_size + 1) * 4), NULL, true);

	math::Vector3* pBuffer = (math::Vector3*)m_pVB->Map(MAP_DISCARD);

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = size/2;
	}

	for(int i = (size / grid_size + 1); i < 2 * (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2 + grid_size * i;
		vertex->y = 0;
		vertex->z = -size/2;
	}

	for(int i = 2 * (size / grid_size + 1); i < 3 * (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = -size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}

	for(int i = 3 * (size / grid_size + 1); i < 4 * (size / grid_size + 1); ++i)
	{
		math::Vector3* vertex = pBuffer + i;

		vertex->x = size/2;
		vertex->y = 0;
		vertex->z = size/2 - grid_size * i;
	}
		
	m_pVB->Unmap();


	int line_count = (size / grid_size + 1) + (size / grid_size + 1) - 2;
	int index_count = line_count * 2;
	m_pIB = pGraphics->CreateBuffer(BT_INDEX_BUFFER, index_count * sizeof(int), NULL, true);

	int * pIB = (int*)m_pIB->Map(MAP_DISCARD);

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		*(pIB + 2* i) = i;
		*(pIB + 2* i + 1) = i + size / grid_size + 1;
	}

	for(int i = 0; i < (size / grid_size + 1); ++i)
	{
		*(pIB + 2* i) = i;
		*(pIB + 2* i + 1) = i + size / grid_size + 1;
	}


	m_pIB->Unmap();


	return true;
}
void GridMesh::Release()
{
}

void GridMesh::Render()
{
}
