#pragma once

#include "core\CoreParameters.h"

namespace engine
{

	class EXPORT_CLASS EngineCore
	{
	public:
		EngineCore(void);
		virtual ~EngineCore(void);

		bool								Initialize(const CoreParameters& param);
		void								Release();
		void								Update();

		void*								MemAlloc(uint64 bytes);
		void								MemFree(void* pMem);

		template<typename Object_T>
		boost::shared_ptr<Object_T>			ObjectAlloc();


		SysGraphicsPtr						GetSysGraphics();
		SysInputPtr							GetSysInput();


	private:
		template<typename Object_T>
		void								ObjectDelete(Object_T* pObj);


		void								update_fps();
	private:
		SysManagerPtr						m_pSysManager;

		SysGraphicsPtr						m_pSysGraphics;
		SysInputPtr							m_pSysInput;

		MemManagerPtr						m_pMemManager;

		GameObjectManagerPtr				m_pGameObjectManager;

	};




	template<typename Object_T>
	inline
		boost::shared_ptr<Object_T>	EngineCore::ObjectAlloc()
	{
		void* pMem = MemAlloc(sizeof(Object_T));

		return boost::shared_ptr<Object_T>(new(pMem) Object_T, boost::bind(&EngineCore::ObjectDelete<Object_T>, this, _1));
	}

	template<typename Object_T>
	inline
		void EngineCore::ObjectDelete(Object_T* pObj)
	{
		pObj->~Object_T();

		MemFree(pObj);
	}
}
