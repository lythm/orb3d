#include "StdAfx.h"
#include "TimerManager.h"
#include <vector>


TimerManager::TimerManager(void)
{
	m_head = NULL;

}


TimerManager::~TimerManager(void)
{
}
bool TimerManager::Init()
{
	m_head = new TimerNode;
	memset(m_head, 0, sizeof(TimerNode));


	return true;
}
void TimerManager::Release()
{
	TimerNode* pNode = m_head->next;

	while(pNode)
	{
		TimerNode* n = pNode;

		pNode = pNode->next;

		delete n;

	}

	m_head->next = NULL;

	delete m_head;
}
void TimerManager::Update()
{
	int tick = GetTickCount();

	TimerNode* pNode = m_head->next;


	std::vector<TimerNode*> l;

	while(pNode)
	{

		if((tick - pNode->start_tick) < pNode->interval)
		{
			break;
		}

		TimerNode* pTmp = pNode;

		pNode = pNode->next;


		pTmp->handler(pTmp, pTmp->interval, pTmp->handler_context);
		

		UnLink(pTmp);

		l.push_back(pTmp);

	}

	for(size_t i = 0; i <l.size(); ++i)
	{
		InsertNode(l[i]);
	}

}
void* TimerManager::RegisterTimer(int interval, void* context, const boost::function<void (void* timer, int interval, void* context)>& handler)
{
	int tick = GetTickCount();

	TimerNode* pNewNode = new TimerNode;
	pNewNode->interval = interval;
	pNewNode->start_tick = tick;
	pNewNode->handler = handler;
	pNewNode->handler_context = context;
	pNewNode->next = NULL;
	pNewNode->prev = NULL;

	InsertNode(pNewNode);

	return pNewNode;
}
void TimerManager::RemoveTimer(void* timer)
{
	if(timer == NULL)
		return;

	TimerNode* pNode = (TimerNode*)timer;

	UnLink(pNode);

	delete pNode;
	

}
void TimerManager::InsertNode(TimerNode* pNewNode)
{
	int tick = GetTickCount();

	pNewNode->start_tick = tick;

	int tn = pNewNode->start_tick + pNewNode->interval;



	TimerNode* pNode = m_head;

	while(pNode)
	{
		TimerNode* pNext = pNode->next;

		if(pNext == NULL)
		{
			pNode->next = pNewNode;
			pNewNode->prev = pNode;
			pNewNode->next = NULL;
			break;
		}


		if((pNext->start_tick + pNext->interval) > tn)
		{
			pNode->next = pNewNode;
			pNewNode->prev = pNode;

			pNewNode->next = pNext;
			pNext->prev = pNewNode;
			break;
		}

		pNode = pNode->next;
	}
}
void TimerManager::UnLink(TimerNode* pNode)
{
	if(pNode == NULL)
		return;

	if(pNode->prev)
	{
		pNode->prev->next = pNode->next;
	}

	if(pNode->next)
	{
		pNode->next->prev = pNode->prev;
	}

	pNode->next = pNode->prev = NULL;

}
