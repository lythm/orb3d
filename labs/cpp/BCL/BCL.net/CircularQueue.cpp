#include "StdAfx.h"
#include "CircularQueue.h"

namespace managed_bcl
{
	CircularQueue::CircularQueue(int bufferBytes)
	{
		m_pQueue = new bcl::CircularQueue(bufferBytes);
	}

	CircularQueue::~CircularQueue(void)
	{
		delete m_pQueue;
		m_pQueue = NULL;
	}

	CircularQueue::Result CircularQueue::Write(array<Byte>^ buffer, int bytes)
	{
		pin_ptr<Byte> p = &buffer[0];
      
		return (Result)m_pQueue->Write(p, bytes);
	}

	CircularQueue::Result CircularQueue::Read(array<Byte>^ buffer, int % bytes)
	{
		pin_ptr<Byte> p = &buffer[0];

		int _bytes = bytes;

		Result ret = (Result)m_pQueue->Read(p, _bytes);

		bytes = _bytes;

		return ret;

	}

	CircularQueue::Result CircularQueue::Peek(array<Byte>^ buffer, int bytes)
	{
		pin_ptr<Byte> p = &buffer[0];
		return (Result)m_pQueue->Peek(p, bytes);
	}

	int CircularQueue::GetDataBytes()
	{
		return m_pQueue->GetDataBytes();
	}

	CircularQueue::Result CircularQueue::Remove(int bytes)
	{
		return (Result)m_pQueue->Remove(bytes);
	}

	void CircularQueue::Reset()
	{
		m_pQueue->Reset();
	}
}
