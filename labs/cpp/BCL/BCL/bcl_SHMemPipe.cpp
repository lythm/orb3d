#include "bcl_types.h"
#include "bcl_SHMemPipe.h"
#include "bcl_SHMemFastChannel.h"


namespace bcl
{
	SHMemPipe::SHMemPipe(void)
	{
		m_pReadChannel					= NULL;

		m_pWriteChannel					= NULL;

	}

	SHMemPipe::~SHMemPipe(void)
	{
	}



	bool SHMemPipe::IsReady()
	{

		if(m_pReadChannel == NULL || m_pWriteChannel == NULL)
		{

			return false;

		}


		if(m_pReadChannel->IsReady() == false || m_pWriteChannel->IsReady() == false)
		{

			return false;

		}

		return true;

	}


	SHMemReturnValue::RetValue SHMemPipe::Open(const wchar_t* szName, DWORD readChannelBytes, DWORD writechannelBytes)
	{
		Close();

		std::wstring name				= szName;

		m_pReadChannel					= new SHMemFastChannel;

		if(m_pReadChannel == NULL)
		{
			
			return SHMemReturnValue::ret_failed;

		}


		std::wstring rcName = name + L"_in";

		if(false == m_pReadChannel->Open(rcName.c_str(), readChannelBytes))
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}

		std::wstring wcName = name + L"_out";

		m_pWriteChannel					= new SHMemFastChannel;

		if(m_pWriteChannel == NULL)
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}

		if(false == m_pWriteChannel->Open(wcName.c_str(), writechannelBytes))
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}


		return SHMemReturnValue::ret_ok;
	}


	void SHMemPipe::Close()
	{

		if(m_pReadChannel)
		{

			m_pReadChannel->Close();

			delete m_pReadChannel;

			m_pReadChannel = NULL;

		}


		if(m_pWriteChannel)
		{
			
			m_pWriteChannel->Close();

			delete m_pWriteChannel;

			m_pWriteChannel = NULL;

		}
	}


	SHMemReturnValue::RetValue	SHMemPipe::Attach(const wchar_t* szName)
	{
		Close();

		std::wstring name				= szName;

		m_pReadChannel					= new SHMemFastChannel;

		if(m_pReadChannel == NULL)
		{
			
			return SHMemReturnValue::ret_failed;

		}


		std::wstring rcName = name + L"_out";

		if(false == m_pReadChannel->Attach(rcName.c_str()))
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}

		std::wstring wcName = name + L"_in";

		m_pWriteChannel					= new SHMemFastChannel;

		if(m_pWriteChannel == NULL)
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}

		if(false == m_pWriteChannel->Attach(wcName.c_str()))
		{

			Close();

			return SHMemReturnValue::ret_failed;

		}


		return SHMemReturnValue::ret_ok;
	}


	


	SHMemReturnValue::RetValue	SHMemPipe::Write(void* pData, DWORD bytes)
	{

		if(IsReady() == false)
		{

			return SHMemReturnValue::ret_not_ready;


		}
		

		return m_pWriteChannel->Write(pData, bytes);

	}


	SHMemReturnValue::RetValue	SHMemPipe::Read(void* pData, DWORD& bytes)
	{

		if(IsReady() == false)
		{

			return SHMemReturnValue::ret_not_ready;

		}


		return m_pReadChannel->Read(pData, bytes);

	}

}