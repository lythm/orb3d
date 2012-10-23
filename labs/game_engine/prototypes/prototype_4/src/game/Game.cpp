#include "game_pch.h"
#include "Game.h"



EXPORT_C_API Game* CreateGame()
{
	return new Game;
}

EXPORT_C_API void DestroyGame(engine::GameInterface* pGame)
{
	delete (Game*)pGame;
}



Game::Game(void)
{

}


Game::~Game(void)
{
}
bool Game::Initialize(engine::CoreApiPtr pCore)
{
	using namespace engine;

	m_pCore = pCore;



	math::Vector3 verts[] = 
	{
		math::Vector3(0, 50, 0),
		math::Vector3(50, 0, 0),
		math::Vector3(0, 0, 0),
	};


	m_pVB = m_pCore->GetSysGraphics()->CreateBuffer(Sys_Graphics::BT_VERTEX_BUFFER, sizeof(math::Vector3) * 3, verts, true);

	void* pData = m_pVB->Map(GPUBuffer::MAP_DISCARD);

	memcpy(pData, verts, sizeof(math::Vector3)*3);
	m_pVB->Unmap();

	uint32 indice[] = {0, 1, 2,};

	m_pIB = m_pCore->GetSysGraphics()->CreateBuffer(Sys_Graphics::BT_INDEX_BUFFER, sizeof(uint32) * 3, indice, true);

	pData = m_pIB->Map(GPUBuffer::MAP_DISCARD);

	memcpy(pData, indice, sizeof(uint32)*3);
	m_pIB->Unmap();


	m_pGFX = m_pCore->GetSysGraphics()->CreateGFXFromFile("./assets/gfx/test.cgfx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,VertexElement::VE_FLOAT3),
	};

	m_pGFX->SetVertexFormat(vf, 1);

	math::Matrix44 view = math::MatrixLookAtLH(math::Vector3(0, 30, -20), math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
	math::Matrix44 proj = math::MatrixPerspectiveFovLH(3.0f/4.0f * 3.14f, 4.0f/ 3.0f, 0.0001f, 10000.0f);

	m_pGFX->SetMatrixBySemantic("WORLDVIEWPROJ", view * proj);

	return true;
}
void Game::Release()
{
	m_pIB->Release();
	m_pVB->Release();
	m_pGFX->Release();


}
bool Game::Update()
{
	using namespace engine;

	static float rad = 0;
	rad += 0.001f;

	math::Vector3 eye(0, 30, -30);

	math::Matrix44 mat = math::MatrixRotationAxisY(rad);

	math::TransformCoord(eye, mat);


	math::Matrix44 view = math::MatrixLookAtLH(eye, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
	math::Matrix44 proj = math::MatrixPerspectiveFovLH(3.0f/4.0f * 3.14f, 4.0f/ 3.0f, 0.0001f, 10000.0f);

	m_pGFX->SetMatrixBySemantic("WORLDVIEWPROJ", view * proj);


	m_pCore->GetSysGraphics()->ClearRenderTarget();


	m_pCore->GetSysGraphics()->SetIndexBuffer(m_pIB, Sys_Graphics::IT_INT32);
	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3));
	m_pCore->GetSysGraphics()->SetPrimitiveType(Sys_Graphics::PT_TRIANGLE_LIST);

	m_pGFX->ApplyVertexFormat();


	while(m_pGFX->BeginPass())
	{
		m_pGFX->ApplyPass();

		m_pCore->GetSysGraphics()->DrawPrimitive(3, 0, 0);

		m_pGFX->EndPass();
	}

	m_pCore->GetSysGraphics()->Present();


	return true;
}
