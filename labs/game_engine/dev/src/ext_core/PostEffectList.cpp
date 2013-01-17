#include "core_ext_pch.h"
#include "..\..\include\core\ext\PostEffectList.h"

#include "core\ext\PropertyManager.h"


namespace ld3d
{

	PostEffectList::PostEffectList(GameObjectManagerPtr pManager) : GameObjectComponent(L"PostEffectList", pManager)
	{
	}


	PostEffectList::~PostEffectList(void)
	{
	}
	const Version& PostEffectList::GetVersion() const
	{
		return g_packageVersion;
	}
	bool PostEffectList::OnAttach()
	{
		m_pSSAO = m_pManager->GetAllocator()->AllocObject<PostEffect_SSAO>();

		m_pSSAO->Initialize(m_pManager->GetRenderSystem());
		
		m_pManager->GetRenderSystem()->AddPostEffect(m_pSSAO);

		m_pGBlur = m_pManager->GetAllocator()->AllocObject<PostEffect_GaussianBlur>();
		m_pGBlur->Initialize(m_pManager->GetRenderSystem());
		//m_pManager->GetRenderSystem()->AddPostEffect(m_pGBlur);

		PropertyManagerPtr pPM = boost::shared_dynamic_cast<PropertyManager>(m_pObject->GetComponent(L"PropertyManager"));

		pPM->Begin(L"PostEffectList");
		{
			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				L"Bias", 
				&PostEffect_SSAO::GetBias,
				&PostEffect_SSAO::SetBias);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				L"Scale", 
				&PostEffect_SSAO::GetScale,
				&PostEffect_SSAO::SetScale);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				L"Sample Rad", 
				&PostEffect_SSAO::GetSampleRad,
				&PostEffect_SSAO::SetSampleRad);

			pPM->RegisterProperty<float, PostEffect_SSAO>(m_pSSAO.get(), 
				L"Intensity", 
				&PostEffect_SSAO::GetIntensity,
				&PostEffect_SSAO::SetIntensity);
		}
		pPM->End();

		return true;
	}
	void PostEffectList::OnDetach()
	{

	}
}
