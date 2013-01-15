#include "game_pch.h"
#include "DefferedShadingDemo.h"


DefferedShadingDemo::DefferedShadingDemo(void)
{
}


DefferedShadingDemo::~DefferedShadingDemo(void)
{
}
bool DefferedShadingDemo::Init(ld3d::CoreApiPtr pCore)
{
	using namespace ld3d;
	m_pCore = pCore;

	m_pCore->AddEventHandler(EV_WINMSG, boost::bind(&DefferedShadingDemo::OnWMEvent, this, _1));

	G_FORMAT formats[3] = 
	{
		G_FORMAT_R16G16B16A16_FLOAT,				// position
		G_FORMAT_R16G16B16A16_FLOAT,				// normal
		G_FORMAT_R32_FLOAT,							// depth
	};

	m_pRT = m_pCore->GetSysGraphics()->CreateRenderTarget(3, 800, 600, formats);

	//DepthStencilBufferPtr pDS = m_pCore->GetSysGraphics()->CreateDepthStencilBuffer(800, 600, G_FORMAT_D32_FLOAT);

	//m_pRT->SetDepthStencilBuffer(pDS);


	CreateScene();
	CreateQuad();

	return true;
}

void DefferedShadingDemo::Release()
{
	m_pTex->Release();
	
	if(m_pIB)
	{

		m_pIB->Release();
	}

	
	m_pVB->Release();
	m_pMaterial->Release();

	m_pQuadMaterial->Release();
	m_pQuadVB->Release();

	m_pRT->Release();
}
void DefferedShadingDemo::Update()
{
	Render();
}

void DefferedShadingDemo::OnWMEvent(ld3d::EventPtr pEvent)
{
	using namespace ld3d;

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
	using namespace ld3d;
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
		{ math::Vector3(-1, 1, 0), math::Vector2(0, 0),},
		{ math::Vector3(1, -1, 0), math::Vector2(1, 1),},
		{ math::Vector3(-1, -1, 0), math::Vector2(0, 1),},
	};

	m_pQuadVB = m_pCore->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, sizeof(Vertex) * 6, verts, true);


	m_pQuadMaterial = m_pCore->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/ds2.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};
	VertexFormat format;

	format.SetElement(vf, 2);

	m_pQuadMaterial->SetVertexFormat(format);
}
void DefferedShadingDemo::CreateScene()
{
	using namespace ld3d;
	m_pTex = m_pCore->GetSysGraphics()->CreateTextureFromFile("./assets/standard/texture/15.png");

	m_pMaterial = m_pCore->GetSysGraphics()->CreateMaterialFromFile("./assets/standard/material/ds1.fx");

	VertexElement vf[] = 
	{
		VertexElement(0, VertexElement::POSITION,G_FORMAT_R32G32B32_FLOAT),
		VertexElement(0, VertexElement::TEXCOORD,G_FORMAT_R32G32_FLOAT),
	};


	m_pMesh = MeshUtil::CreateSphere(20, 100, 100, m_pMaterial);
	//m_pMesh = MeshUtil::CreateCube(10, m_pMaterial);
	
	m_pVB = m_pCore->GetSysGraphics()->CreateBuffer(BT_VERTEX_BUFFER, m_pMesh->GetVertexDataBytes(), m_pMesh->GetVertexData(), false);
	
	if(m_pMesh->GetSubMesh(0)->IsIndexed())
	{
		m_pIB = m_pCore->GetSysGraphics()->CreateBuffer(BT_INDEX_BUFFER, m_pMesh->GetIndexDataBytes(), m_pMesh->GetIndexData(), false);
	}
	m_pMaterial->SetTextureByName("diff_tex", m_pTex);
}


void DefferedShadingDemo::Render()
{
	DrawScene();
	DrawQuad();

	m_pCore->GetSysGraphics()->Present();
}
void DefferedShadingDemo::DrawQuad()
{
	using namespace ld3d;
	m_pCore->GetSysGraphics()->SetRenderTarget(RenderTargetPtr());

	m_pCore->GetSysGraphics()->ClearRenderTarget(RenderTargetPtr(), 0, math::Color4(1.0, 1.0, 1.0, 1));
	m_pCore->GetSysGraphics()->ClearDepthStencilBuffer(DepthStencilBufferPtr(), CLEAR_ALL, 1, 0);

	m_pQuadMaterial->SetTextureByName("pos_tex", m_pRT->AsTexture(0));
	m_pQuadMaterial->SetTextureByName("normal_tex", m_pRT->AsTexture(1));
	m_pQuadMaterial->SetTextureByName("depth_tex", m_pRT->AsTexture(2));

	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pQuadVB, 0, sizeof(math::Vector3) + sizeof(math::Vector2));
	m_pCore->GetSysGraphics()->SetPrimitiveType(PT_TRIANGLE_LIST);
	
	m_pQuadMaterial->ApplyVertexFormat();
	
	int nPass = 0;

	m_pQuadMaterial->Begin(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pQuadMaterial->ApplyPass(i);
		m_pCore->GetSysGraphics()->Draw(6, 0);
	}

	m_pQuadMaterial->End();
}
void DefferedShadingDemo::DrawScene()
{
	using namespace ld3d;

	m_pCore->GetSysGraphics()->SetRenderTarget(m_pRT);
	m_pCore->GetSysGraphics()->ClearDepthStencilBuffer(m_pRT->GetDepthStencilBuffer(), CLEAR_ALL, 0.999999f, 0);
	
	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT, 0, math::Color4(0.0, 0.0, 0.0, 1));
	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT, 1, math::Color4(0.0, 0.0, -1.0, 1));
	m_pCore->GetSysGraphics()->ClearRenderTarget(m_pRT, 2, math::Color4(1.0, 1, 1, 1));

	static int tick = GetTickCount();

	int dt = GetTickCount() - tick;

	float angle = 3.14f * (dt / 2000.0f);

	tick = GetTickCount();
	using namespace ld3d;

	static float rad = 0;
	rad += angle;

	math::Vector3 eye(0, 30, -30);

	math::Matrix44 mat = math::MatrixRotationAxisY(rad);

	math::TransformCoord(eye, mat);
	
	math::Matrix44 view = math::MatrixLookAtLH(eye, math::Vector3(0, 0, 0), math::Vector3(0, 1, 0));
	math::Matrix44 proj = math::MatrixPerspectiveFovLH(1.0f/2.0f * 3.14f, 4.0f/ 3.0f, 0.0001f, 10000.0f);

	m_pMaterial->SetMatrixBySemantic("MATRIX_WVP", view * proj);
	m_pMaterial->SetMatrixBySemantic("MATRIX_WV", view);
	m_pQuadMaterial->SetMatrixBySemantic("MATRIX_WV", view);

	if(m_pMesh->GetSubMesh(0)->IsIndexed())
	{
		m_pCore->GetSysGraphics()->SetIndexBuffer(m_pIB, G_FORMAT_R16_UINT);
	}
	m_pCore->GetSysGraphics()->SetVertexBuffer(m_pVB, 0, m_pMesh->GetSubMesh(0)->GetVertexStride());
	m_pCore->GetSysGraphics()->SetPrimitiveType(m_pMesh->GetSubMesh(0)->GetPrimitiveType());
	
	m_pMaterial->ApplyVertexFormat();
	
	int nPass = 0;

	m_pMaterial->Begin(nPass);

	for(int i = 0; i < nPass; ++i)
	{
		m_pMaterial->ApplyPass(i);

		if(m_pMesh->GetSubMesh(0)->IsIndexed())
		{
			m_pCore->GetSysGraphics()->DrawIndexed(m_pMesh->GetSubMesh(0)->GetIndexCount(),0, 0);
		}
		else
		{
			m_pCore->GetSysGraphics()->Draw(m_pMesh->GetSubMesh(0)->GetVertexCount(), 0);
		}


		//m_pCore->GetSysGraphics()->DrawIndexed(6, 0, 0);
		
	}

	m_pMaterial->End();
}
