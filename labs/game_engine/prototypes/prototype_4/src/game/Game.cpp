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


	m_pTex = m_pCore->GetSysGraphics()->CreateTextureFromFile("./15.png");

	struct Vertex
	{
		math::Vector3			pos;
		math::Vector2			uv;
	};

	Vertex verts[] = 
	{
		{ math::Vector3(10, 10, -10), math::Vector2(1, 0),},
		{ math::Vector3(10, -10, -10), math::Vector2(1, 1),},
		{ math::Vector3(-10, -10, -10), math::Vector2(0, 1),},
		{ math::Vector3(-10, 10, -10), math::Vector2(0, 0),},


		{ math::Vector3(10, 10, 10), math::Vector2(0, 1),},
		{ math::Vector3(10, -10, 10),math::Vector2(1, 1),},
		{ math::Vector3(-10, -10, 10),math::Vector2(0, 1),},
		{ math::Vector3(-10, 10, 10),math::Vector2(0, 0),},
	};

	m_pVB = m_pCore->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, sizeof(Vertex) * 8, verts, true);

	
	uint32 indice[] = 
	{
		0, 1, 2,
		0, 2, 3,

		4, 6, 5,
		4, 7, 6,

		0, 3, 4,
		4, 3, 7,

		1, 5, 6,
		1, 6, 2,

		0, 4, 5,
		0, 5, 1,

		3, 2, 6,
		3, 6, 7,
	};

	m_pIB = m_pCore->GetSysGraphics()->CreateBuffer(BT_INDEX_BUFFER, sizeof(uint32) * 36, indice, true);

	m_pGFX = m_pCore->GetSysGraphics()->CreateGFXFromFile("./assets/gfx/test.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};

	m_pGFX->SetVertexFormat(vf, 2);


	m_pGFX->SetTextureByName("diff_tex", m_pTex);

	m_pRT = m_pCore->GetSysGraphics()->CreateRenderTarget(1024, 1024, G_FORMAT_R8G8B8A8_UNORM, 1);

	DepthStencilBufferPtr pDS = m_pCore->GetSysGraphics()->CreateDepthStencilBuffer(1024, 1024, G_FORMAT_D32_FLOAT);

	m_pRT->AttachDepthStencilBuffer(pDS);
	return true;
}
void Game::Release()
{
	m_pRT->Release();
	m_pTex->Release();
	m_pIB->Release();
	m_pVB->Release();
	m_pGFX->Release();

}
bool Game::Update()
{
	static int tick = GetTickCount();

	int dt = GetTickCount() - tick;

	float angle = 3.14 * (dt / 1000.0f);

	tick = GetTickCount();
	using namespace engine;

	static float rad = 0;
	rad += angle;

	math::Vector3 eye(0, 0, -30);

	math::Matrix44 mat = math::MatrixRotationAxisY(rad);

	math::TransformCoord(eye, mat);


	math::Matrix44 view = math::MatrixLookAtLH(eye, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
	math::Matrix44 proj = math::MatrixPerspectiveFovLH(1.0f/2.0f * 3.14f, 4.0f/ 3.0f, 0.0001f, 10000.0f);

	m_pGFX->SetMatrixBySemantic("MATRIX_WVP", view * proj);

	m_pGFX->SetTextureByName("diff_tex", m_pTex);
	m_pCore->GetSysGraphics()->ClearFrameBuffer();

	m_pRT->Clear(math::Color4(0.5, 0.5, 0, 0), 1.0f, 0);
	m_pCore->GetSysGraphics()->SetRenderTarget(m_pRT);

	m_pCore->GetSysGraphics()->SetIndexBuffer(m_pIB, G_FORMAT_R32_UINT);
	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3) + sizeof(math::Vector2));
	m_pCore->GetSysGraphics()->SetPrimitiveType(PT_TRIANGLE_LIST);

	m_pGFX->ApplyVertexFormat();


	int nPass = 0;

	m_pGFX->BeginPass(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pGFX->ApplyPass(i);

		m_pCore->GetSysGraphics()->DrawPrimitive(36, 0, 0);
	}

	m_pGFX->EndPass();

	///////////////////////////////////

	m_pCore->GetSysGraphics()->SetRenderTarget(RenderTargetPtr());

	m_pGFX->SetTextureByName("diff_tex", m_pRT->AsTexture());
	m_pGFX->BeginPass(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pGFX->ApplyPass(i);

		m_pCore->GetSysGraphics()->DrawPrimitive(36, 0, 0);
	}

	m_pGFX->EndPass();

	m_pCore->GetSysGraphics()->Present();

	return true;
}
