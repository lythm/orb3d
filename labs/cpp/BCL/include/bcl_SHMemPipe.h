#pragma once

#include "bcl_SHMemReturnValue.h"


namespace bcl
{
	class SHMemFastChannel;



	class DLL_EXPORT SHMemPipe
	{

	public:


		SHMemPipe(void);


		virtual ~SHMemPipe(void);


		SHMemReturnValue::RetValue				Open(const wchar_t* szName, DWORD readChannelBytes, DWORD writechannelBytes);


		SHMemReturnValue::RetValue				Attach(const wchar_t* szName);


		void									Close();
		
		bool									IsReady();

		
		SHMemReturnValue::RetValue				Write(void* pData, DWORD bytes);


		SHMemReturnValue::RetValue				Read(void* pData, DWORD& bytes);



	private:


		SHMemFastChannel*						m_pReadChannel;

		SHMemFastChannel*						m_pWriteChannel;

	};

}