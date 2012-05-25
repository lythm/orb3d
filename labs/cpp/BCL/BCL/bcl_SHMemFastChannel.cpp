#include "bcl_types.h"
#include "bcl_SHMemFastChannel.h"


namespace bcl
{
	SHMemFastChannel::SHMemFastChannel(void)
	{
		m_hMapObject						= NULL;

		m_pHeader							= NULL;

		m_hDataAvailable						= NULL;

	}

	SHMemFastChannel::~SHMemFastChannel(void)
	{
	}



	bool SHMemFastChannel::Attach(const wchar_t* szName)
	{
		std::wstring pipeName				= szName;

	
		std::wstring eventName				= pipeName + L"_data";

		m_hDataAvailable						= OpenEvent(EVENT_ALL_ACCESS , FALSE, eventName.c_str());


		if(m_hDataAvailable == NULL)
		{

			Close();

			return false;

		}


		m_hMapObject						= OpenFileMapping(FILE_MAP_WRITE,FALSE,szName);


		if(m_hMapObject == NULL)
		{

			Close();

			return false;

		}


		m_pHeader							= (Header*)MapViewOfFile(m_hMapObject, FILE_MAP_WRITE, 0, 0, 0);


		if(m_pHeader == NULL)
		{

			Close();

			return false;

		}


		return true;
	}


	bool SHMemFastChannel::Open(const wchar_t* szName, DWORD bytes)
	{
		std::wstring pipeName						= szName;

		
		m_hMapObject								= CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, bytes + sizeof(Header), szName);


		if(m_hMapObject == NULL)
		{

			return false;

		}


		DWORD error									= GetLastError();


		if(error == ERROR_ALREADY_EXISTS)
		{

			Close();

			return false;

		}


		m_pHeader									= (Header*)MapViewOfFile(m_hMapObject, FILE_MAP_WRITE, 0, 0, 0);


		if(m_pHeader == NULL)
		{

			Close();

			return false;

		}

		m_pHeader->m_channelBytes					= bytes;

		m_pHeader->m_readPos						= sizeof(Header);

		m_pHeader->m_writePos						= sizeof(Header);

		m_pHeader->m_dataBytes						= 0;


		std::wstring eventName						= pipeName + L"_data";
		
		m_hDataAvailable								= CreateEvent(NULL, FALSE, FALSE, eventName.c_str());


		if(m_hDataAvailable == NULL)
		{

			Close();

			return false;


		}
		return true;
	}


	void SHMemFastChannel::Close()
	{
		if(m_pHeader)
		{

			UnmapViewOfFile(m_pHeader);

			m_pHeader = NULL;

		}


		if(m_hMapObject)
		{

			CloseHandle(m_hMapObject);

			m_hMapObject = NULL;

		}


		if(m_hDataAvailable)
		{

			CloseHandle(m_hDataAvailable);

			m_hDataAvailable = NULL;

		}

	}


	SHMemReturnValue::RetValue SHMemFastChannel::Write(void* pData, DWORD bytes)
	{
		LONG dataBytes						= m_pHeader->m_dataBytes;

		DWORD blankBytes					=  m_pHeader->m_channelBytes - dataBytes;
		

		// not enough room to write
		if(blankBytes < bytes)
		{

			return SHMemReturnValue::ret_buffer_overflow;

		}
		

		BYTE* pos							= m_pHeader->m_writePos + (BYTE*)m_pHeader;
		
		
		// bytes to the end of the buffer
		DWORD bytesToEnd					= m_pHeader->m_channelBytes - m_pHeader->m_writePos;

		if(bytesToEnd >= bytes)
		{
			memcpy_s(pos, bytesToEnd, pData, bytes);

			m_pHeader->m_writePos += bytes;

			InterlockedExchangeAdd(&m_pHeader->m_dataBytes, bytes);


			SetEvent(m_hDataAvailable);


			return SHMemReturnValue::ret_ok;
		}

		memcpy_s(pos, bytesToEnd, pData, bytesToEnd);

		pos									= (BYTE*)m_pHeader + sizeof(Header);

		memcpy(pos, (BYTE*)pData + bytesToEnd, bytes - bytesToEnd);

		m_pHeader->m_writePos  = sizeof(Header) + bytes - bytesToEnd;

		InterlockedExchangeAdd(&m_pHeader->m_dataBytes, bytes);

		SetEvent(m_hDataAvailable);

		return SHMemReturnValue::ret_ok;

	}

	SHMemReturnValue::RetValue SHMemFastChannel::Read(void* pData, DWORD& bytes)
	{
		if(m_pHeader->m_dataBytes == 0)
		{
			SHMemReturnValue::RetValue ret	= WaitForData();

			if(ret != SHMemReturnValue::ret_ok)
			{
				return ret;
			}
		}

		LONG dataBytes						= m_pHeader->m_dataBytes;

		bytes = ((DWORD)dataBytes >= bytes) ? bytes : dataBytes;
		
		BYTE* pos = (BYTE*)m_pHeader + m_pHeader->m_readPos;

		DWORD bytesToEnd = m_pHeader->m_channelBytes - m_pHeader->m_readPos;

		if(bytesToEnd >= bytes)
		{
			memcpy_s(pData, bytes, pos, bytes);

			m_pHeader->m_readPos += bytes;

			InterlockedExchangeAdd(&m_pHeader->m_dataBytes,  -(LONG)bytes);

			return SHMemReturnValue::ret_ok;
		}


		memcpy_s(pData, bytes, pos, bytesToEnd);

		pos									= (BYTE*)m_pHeader + sizeof(Header);

		memcpy((BYTE*)pData + bytesToEnd, pos, bytes - bytesToEnd);


		m_pHeader->m_readPos = sizeof(Header) + bytes - bytesToEnd;

		
		InterlockedExchangeAdd(&m_pHeader->m_dataBytes, -(LONG)bytes);
		

		return SHMemReturnValue::ret_ok;

	}


	SHMemReturnValue::RetValue SHMemFastChannel::WaitForData(int timeout)
	{
		DWORD ret							= WaitForSingleObject(m_hDataAvailable, timeout);


		if(ret == WAIT_TIMEOUT)
		{

			return SHMemReturnValue::ret_timeout;

		}


		if(ret == WAIT_OBJECT_0)
		{

			return SHMemReturnValue::ret_ok;

		}


		if(ret == WAIT_ABANDONED)
		{

			return SHMemReturnValue::ret_channel_closed;

		}


		return SHMemReturnValue::ret_failed;
	}

	bool SHMemFastChannel::IsReady()
	{
		if(NULL == m_hMapObject)
		{

			return false;

		}

		
		if(NULL == m_pHeader)
		{
			
			return false;

		}


		if(m_hDataAvailable == NULL)
		{
			
			return false;

		}


		return true;
	}
}

