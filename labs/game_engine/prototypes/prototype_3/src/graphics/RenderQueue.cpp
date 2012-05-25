#include "graphics_pch.h"
#include "RenderQueue.h"

namespace engine
{
	RenderQueue::RenderQueue(void)
	{
	
	}


	RenderQueue::~RenderQueue(void)
	{
	}
	void RenderQueue::Push(RenderDataPtr pData)
	{
		m_queue.push_back(pData);
	}
	void RenderQueue::Clear()
	{
		m_queue.clear();
	}
	RenderDataPtr RenderQueue::GetAt(uint32 index)
	{
		return m_queue[index];
	}
	uint32 RenderQueue::GetLength()
	{
		return (uint32)m_queue.size();
	}
}
