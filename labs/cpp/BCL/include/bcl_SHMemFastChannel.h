#pragma once

#include "bcl_SHMemReturnValue.h"


namespace bcl
{
	class DLL_EXPORT SHMemFastChannel
	{


#pragma pack(push, 8)

		struct Header
		{

			DWORD					m_readPos;


			DWORD					m_writePos;


			DWORD					m_channelBytes;

			volatile LONG			m_dataBytes;

		};

#pragma pack(pop)



	public:


		SHMemFastChannel(void);


		virtual ~SHMemFastChannel(void);

		bool									IsReady();


		bool									Open(const wchar_t* szName, DWORD bytes);


		bool									Attach(const wchar_t* szName);


		void									Close();


		SHMemReturnValue::RetValue				Write(void* pData, DWORD bytes);


		SHMemReturnValue::RetValue				Read(void* pData, DWORD& bytes);


	private:
		
		SHMemReturnValue::RetValue				WaitForData(int timeout = INFINITE);


	private:

		HANDLE									m_hMapObject;

		Header*									m_pHeader;

		HANDLE									m_hDataAvailable;

	};

}
