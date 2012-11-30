#include "StdAfx.h"
#include "GridMesh.h"
#include "AppContext.h"


GridMesh::GridMesh(void)
{
}


GridMesh::~GridMesh(void)
{
}
bool GridMesh::Init(int size, int grid_size)
{
	using namespace engine;

	m_size = size;
	m_gridSize = grid_size;
	
	Sys_GraphicsPtr pGraphics = AppContext::GetSysGraphics();
	
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

	m_pGFX = pGraphics->CreateGFXFromFile("./assets/gfx/editor_grid.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};

	m_pGFX->SetVertexFormat(vf, 2);




	return true;
}
void GridMesh::Release()
{
	m_pIB->Release();
	m_pVB->Release();
	m_pGFX->Release();
}

void GridMesh::Render(engine::Sys_GraphicsPtr pGraphics)
{
	using namespace engine;

	using namespace math;


	int size = m_size;
	int grid_size = m_gridSize;

	int line_count = (size / grid_size + 1) + (size / grid_size + 1) ;
	int index_count = line_count * 2;

	pGraphics->SetIndexBuffer(m_pIB, G_FORMAT_R32_UINT);
	pGraphics->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
	pGraphics->SetPrimitiveType(PT_LINE_LIST);

	m_pGFX->ApplyVertexFormat();
	
	int nPass = 0;

	m_pGFX->BeginPass(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pGFX->ApplyPass(i);

		pGraphics->DrawPrimitive(index_count, 0, 0);
	}

	m_pGFX->EndPass();

}
engine::GFXPtr GridMesh::GetGFX()
{
	return m_pGFX;
}
math::Matrix44 GridMesh::GetWorldMatrix()
{
	math::Matrix44 mat;
	mat.MakeIdentity();
	return mat;
	
}
void GridMesh::Render_Depth(engine::Sys_GraphicsPtr pSysGraphics)
{
}
