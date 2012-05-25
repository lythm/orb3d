#pragma once


namespace engine
{
	class EXPORT_CLASS GameEngine
	{
	public:
		GameEngine(void);
		virtual ~GameEngine(void);


		bool							Initialize(const CoreParameters& param);
		void							Release();
		
		EngineCorePtr					GetEngineCore();

		SysInputPtr						GetSysInput();
		SysGraphicsPtr					GetSysGraphics();


		void*							MemAlloc(uint64 bytes);
		void							MemFree(void* pMem);
	private:
	
		EngineCorePtr					m_pEngineCore;

	private:
	};


}
