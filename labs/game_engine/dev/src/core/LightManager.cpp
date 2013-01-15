#include "core_pch.h"
#include "..\..\include\core\LightManager.h"
#include "core\Light.h"
#include "core_utils.h"
#include "core\Sys_Graphics.h"
#include "core\Material.h"
#include "core\RenderSystem.h"

namespace ld3d
{
	LightManager::LightManager(void)
	{
		m_lightCount = 0;
	}


	LightManager::~LightManager(void)
	{
	}
	bool LightManager::Initialize(RenderSystemPtr pRS)
	{
		m_pRenderSystem = pRS;
		m_pGraphics = pRS->GetSysGraphics();
		m_lightCount = 0;
		m_pList = LightPtr();

		
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

			pDel->Release();
		}
		m_pList.reset();
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
			m_pList->m_pPrev = pLight;
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

	
	void LightManager::RenderLights()
	{
		LightPtr pLight = GetNextAffectingLight(LightPtr(), ViewFrustum());
		while(pLight)
		{
			if(pLight->GetEnabled())
			{
				pLight->RenderLight(m_pRenderSystem);
			}
			pLight = GetNextAffectingLight(pLight, ViewFrustum());
		}
	}
	
}
