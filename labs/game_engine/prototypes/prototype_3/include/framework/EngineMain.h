#pragma once


namespace engine
{
	class EXPORT_CLASS EngineMain
	{
	public:
		EngineMain(void);
		virtual ~EngineMain(void);

		bool							Initialize(const EngineParameters& param);
		void							Release();
		bool							Update();

		GameEnginePtr					GetEngine();

	private:

		EngineConfigPtr					m_pEngineConfig;
		GameManagerPtr					m_pGameManager;
		GameEnginePtr					m_pGameEngine;
				

	};


}