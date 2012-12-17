#include "core_pch.h"
#include "..\..\include\core\LightManager.h"
#include "core\Light.h"
#include "core_utils.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
namespace engine
{
	LightManager::LightManager(void)
	{
		m_lightCount = 0;
	}


	LightManager::~LightManager(void)
	{
	}
	bool LightManager::Initialize(Sys_GraphicsPtr pGraphics)
	{
		m_pGraphics = pGraphics;
		m_lightCount = 0;
		m_pList = LightPtr();

		m_pLightMaterial = m_pGraphics->CreateMaterialFromFile("./assets/material/dr_light.fx");

		VertexFormat vf;
		vf.AddElement(VertexElement(0, VertexElement::POSITION, G_FORMAT_R32G32B32_FLOAT));
		m_pLightMaterial->SetVertexFormat(vf);

		if(m_pLightMaterial == nullptr)
		{
			return false;
		}
		return true;
	}
	void LightManager::Release()
	{
		LightPtr pNode = m_pList;
		while(pNode)
		{
			LightPtr pDel = pNode;
			pNode = pNode->m_pNext;

			pDel->m_pNext = LightPtr();
			pDel->m_pPrev = LightPtr();
		}
		m_pList.reset();
		if(m_pLightMaterial)
		{
			m_pLightMaterial->Release();
			m_pLightMaterial.reset();
		}
	}
	void LightManager::AddLight(LightPtr pLight)
	{
		if(pLight == nullptr)
		{
			return;
		}

		if(m_pList == nullptr)
		{
			pLight->m_pNext = LightPtr();
			pLight->m_pPrev = LightPtr();
			m_pList = pLight;
		}
		else
		{
			pLight->m_pPrev = LightPtr();
			pLight->m_pNext = m_pList;
			m_pList = pLight;
		}

		m_lightCount++;
	}
	void LightManager::RemoveLight(LightPtr pLight)
	{
		if(pLight == nullptr)
		{
			return;
		}

		if(pLight == m_pList)
		{
			m_pList = pLight->m_pNext;
		}


		if(pLight->m_pNext)
		{
			pLight->m_pNext->m_pPrev = pLight->m_pPrev;
		}
		if(pLight->m_pPrev)
		{
			pLight->m_pPrev->m_pNext = pLight->m_pNext;
		}

		pLight->m_pNext = LightPtr();
		pLight->m_pPrev = LightPtr();

		
		m_lightCount--;
	}
	int	LightManager::GetLightCount()
	{
		return m_lightCount;
	}
	LightPtr LightManager::GetNextLight(LightPtr pLight)
	{
		if(m_pList == nullptr)
		{
			return LightPtr();
		}

		if(pLight == nullptr)
		{
			return m_pList;
		}

		return pLight->m_pNext;
	}
	LightPtr LightManager::GetNextAffectingLight(LightPtr pLight, const ViewFrustum& frustum)
	{
		LightPtr pNode = GetNextLight(pLight);
		
		while(pNode)
		{
			if(pNode->IsAffecting(frustum))
			{
				return pNode;
			}
			pNode = GetNextLight(pNode);
		}
		
		return pNode;
	}

	MaterialPtr	LightManager::GetLightMaterial()
	{
		return m_pLightMaterial;
	}
	void LightManager::RenderLights(MultiRenderTargetPtr pGBuffer)
	{
		LightPtr pLight = GetNextAffectingLight(LightPtr(), ViewFrustum());
		while(pLight)
		{
			RenderLight(pGBuffer, pLight);
			pLight = GetNextAffectingLight(pLight, ViewFrustum());
		}
	}
	void LightManager::RenderLight(MultiRenderTargetPtr pGBuffer, LightPtr pLight)
	{
		const math::Matrix44& tm = pLight->GetWorldTM();

		math::Vector3 d = tm.GetRow3(2);

		m_pLightMaterial->SetVectorByName("v_dir_light", d);
		m_pLightMaterial->SetGBuffer(pGBuffer);
		m_pLightMaterial->ApplyVertexFormat();
		
		
		int nPass = 0;

		m_pLightMaterial->Begin(nPass);
		
		for(int i = 0; i < nPass; ++i)
		{
			m_pLightMaterial->ApplyPass(i);
			pLight->DrawLightVolumn(m_pGraphics);
		}
		m_pLightMaterial->End();
	}
}
