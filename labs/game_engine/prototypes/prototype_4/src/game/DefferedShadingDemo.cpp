#include "game_pch.h"
#include "DefferedShadingDemo.h"


DefferedShadingDemo::DefferedShadingDemo(void)
{
}


DefferedShadingDemo::~DefferedShadingDemo(void)
{
}
bool DefferedShadingDemo::Init(engine::CoreApiPtr pCore)
{
	using namespace engine;
	m_pCore = pCore;

	m_pCore->AddEventHandler(EV_WINDOWSMSG, boost::bind(&DefferedShadingDemo::OnWMEvent, this, _1));

	G_FORMAT formats[3] = 
	{
		G_FORMAT_R8G8B8A8_UNORM,				// position
		G_FORMAT_R8G8B8A8_UNORM,				// normal
		G_FORMAT_R32_FLOAT,						// depth
	};

	m_pRT = m_pCore->GetSysGraphics()->CreateMultiRenderTarget(3, 800, 600, formats);

	CreateScene();
	CreateQuad();

	return true;
}

void DefferedShadingDemo::Release()
{
	m_pTex->Release();
	m_pIB->Release();
	m_pVB->Release();
	m_pGFX->Release();

	m_pQuadGFX->Release();
	m_pQuadIB->Release();
	m_pQuadVB->Release();

	m_pRT->Release();
}
void DefferedShadingDemo::Update()
{
	Render();
}

void DefferedShadingDemo::OnWMEvent(engine::EventPtr pEvent)
{
	using namespace engine;

	const MSG& msg = ((WMEvent*)pEvent.get())->msg;

	switch(msg.message)
	{
	case WM_KEYDOWN:
		{
			if(msg.wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
			}
		}
		break;
	default:
		break;
	}
}
void DefferedShadingDemo::CreateQuad()
{
	using namespace engine;
	struct Vertex
	{
		math::Vector3			pos;
		math::Vector2			uv;
	};

	Vertex verts[] = 
	{
		{ math::Vector3(-1, 1, 0), math::Vector2(0, 0),},
		{ math::Vector3(1, 1, 0), math::Vector2(1, 0),},
		{ math::Vector3(1, -1, 0), math::Vector2(1, 1),},
		{ math::Vector3(-1, -1, 0), math::Vector2(0, 1),},
	};

	m_pQuadVB = m_pCore->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, sizeof(Vertex) * 4, verts, true);


	uint32 indice[] = 
	{
		0, 1, 3,
		1, 2, 3,
	};

	m_pQuadIB = m_pCore->GetSysGraphics()->CreateBuffer(BT_INDEX_BUFFER, sizeof(uint32) * 6, indice, true);

	m_pQuadGFX = m_pCore->GetSysGraphics()->CreateGFXFromFile("./assets/gfx/test2.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};

	m_pQuadGFX->SetVertexFormat(vf, 2);
}
void DefferedShadingDemo::CreateScene()
{
	using namespace engine;
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

	m_pGFX = m_pCore->GetSysGraphics()->CreateGFXFromFile("./assets/gfx/test1.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};

	m_pGFX->SetVertexFormat(vf, 2);
	m_pGFX->SetTextureByName("diff_tex", m_pTex);
}


void DefferedShadingDemo::Render()
{
	DrawScene();
	DrawQuad();

	m_pCore->GetSysGraphics()->Present();
}
void DefferedShadingDemo::DrawQuad()
{
	using namespace engine;
	m_pCore->GetSysGraphics()->SetRenderTarget(RenderTargetPtr());

	m_pCore->GetSysGraphics()->ClearRenderTarget(RenderTargetPtr(), math::Color4(0.0, 0.0, 0.0, 1), 1, 0, CLEAR_ALL);

	m_pQuadGFX->SetTextureByName("pos_tex", m_pRT->AsTexture(0));
	m_pQuadGFX->SetTextureByName("normal_tex", m_pRT->AsTexture(1));
	m_pQuadGFX->SetTextureByName("depth_tex", m_pRT->AsTexture(2));

	m_pCore->GetSysGraphics()->SetIndexBuffer(m_pQuadIB, G_FORMAT_R32_UINT);
	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pQuadVB, 0, sizeof(math::Vector3) + sizeof(math::Vector2));
	m_pCore->GetSysGraphics()->SetPrimitiveType(PT_TRIANGLE_LIST);
	
	m_pQuadGFX->ApplyVertexFormat();
	
	int nPass = 0;

	m_pQuadGFX->BeginPass(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pQuadGFX->ApplyPass(i);
		m_pCore->GetSysGraphics()->DrawPrimitive(6, 0, 0);
	}

	m_pQuadGFX->EndPass();
}
void DefferedShadingDemo::DrawScene()
{
	using namespace engine;
	static int tick = GetTickCount();

	int dt = GetTickCount() - tick;

	float angle = 3.14 * (dt / 20000.0f);

	tick = GetTickCount();
	using namespace engine;

	static float rad = 0;
	rad += angle;

	math::Vector3 eye(0, 30, 30);

	math::Matrix44 mat = math::MatrixRotationAxisY(rad);

	math::TransformCoord(eye, mat);


	math::Matrix44 view = math::MatrixLookAtLH(eye, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
	math::Matrix44 proj = math::MatrixPerspectiveFovLH(1.0f/2.0f * 3.14f, 4.0f/ 3.0f, 0.0001f, 10000.0f);

	m_pGFX->SetMatrixBySemantic("MATRIX_WVP", view * proj);

	m_pCore->GetSysGraphics()->SetIndexBuffer(m_pIB, G_FORMAT_R32_UINT);
	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pVB, 0, sizeof(math::Vector3) + sizeof(math::Vector2));
	m_pCore->GetSysGraphics()->SetPrimitiveType(PT_TRIANGLE_LIST);
	
	m_pGFX->ApplyVertexFormat();
	


	m_pCore->GetSysGraphics()->SetRenderTarget(m_pRT);

	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT->GetRenderTarget(0), math::Color4(0.0, 0.0, 0.0, 1), 1, 0, CLEAR_ALL);
	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT->GetRenderTarget(1), math::Color4(0.0, 0.0, 0.0, 1), 1, 0, CLEAR_ALL);
	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT->GetRenderTarget(2), math::Color4(1.0, 1.0, 1.0, 1), 1, 0, CLEAR_ALL);

	int nPass = 0;

	m_pGFX->BeginPass(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pGFX->ApplyPass(i);
		m_pCore->GetSysGraphics()->DrawPrimitive(36, 0, 0);
	}

	m_pGFX->EndPass();
}
