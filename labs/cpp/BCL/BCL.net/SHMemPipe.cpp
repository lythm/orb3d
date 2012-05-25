#include "StdAfx.h"
#include "SHMemPipe.h"
#include "vcclr.h"
namespace managed_bcl
{
	SHMemPipe::SHMemPipe(void)
	{
		m_pPipe				= new bcl::SHMemPipe();
	}

	SHMemPipe::~SHMemPipe(void)
	{
		if(m_pPipe)
		{
			m_pPipe->Close();
			delete m_pPipe;
		}
	}

	SHMemPipe::Result SHMemPipe::Open(String^ pipeName, UInt32 readChannelBytes, UInt32 writeChannelBytes)
	{
		pin_ptr<const wchar_t> unmngStr = PtrToStringChars(pipeName);

		return (Result)m_pPipe->Open(unmngStr, readChannelBytes, writeChannelBytes);
	}
	SHMemPipe::Result SHMemPipe::Attach(String^ pipeName)
	{
		pin_ptr<const wchar_t> unmngStr = PtrToStringChars(pipeName);

		return (Result)m_pPipe->Attach(unmngStr);
	}


	void SHMemPipe::Close()
	{
		m_pPipe->Close();
	}

	bool SHMemPipe::IsReady()
	{
		return m_pPipe->IsReady();
	}


	SHMemPipe::Result SHMemPipe::Write(array<Byte>^ buffer, int bytes)
	{
		pin_ptr<Byte> p = &buffer[0];
      

		return (Result)m_pPipe->Write(p, bytes);
	}


	SHMemPipe::Result SHMemPipe::Read(array<Byte>^ buffer, int% bytes)
	{
		pin_ptr<Byte> p = &buffer[0];

		DWORD _bytes = bytes;

		Result ret = (Result)m_pPipe->Read(p, _bytes);

		bytes = _bytes;

		return ret;
	}
}