#pragma once


#include "osal/os_all.h"

namespace orb
{

	namespace bcl
	{
		template<typename T>
		class ConcurrentQueue_T 
		{
		public:

			struct Node
			{
				T					value;
				Node*				next;
			};

			ConcurrentQueue_T(void)
			{
			}

			// non-virtual, no derived class please.
			~ConcurrentQueue_T(void)
			{
			}

			void Init()
			{
				Node* node = AllocNode();
				node->next = NULL;

				m_head = m_tail = node;
				
			//	os::cs_initialize(m_hLock);
				//os::cs_initialize(m_tLock);
				
			}

			void Push(T val)
			{
				Node* node = AllocNode();
				node->value = val;
				node->next = NULL;

				//os::cs_enter(m_tLock);
				{
					m_tail->next = node;
					m_tail = node;
				}
				//os::cs_leav(m_tLock);
				
			}
			bool Pop(T& val)
			{
				Node* node = NULL;
			//	os::cs_enter(m_hLock);
				{
					node = m_head;
					Node* new_head = node->next;

					if(new_head == NULL)
					{
						//os::cs_leave(m_hLock);
						return false;
					}

					val = new_head->val;
					m_head = new_head;
				}
			//	os::cs_leave(m_hLock);
					
				FreeNode(node);

				return true;
     		}

			Node* AllocNode()
			{
				return new Node;
			}
			void FreeNode(Node* pNode)
			{
				delete pNode;
			}

		private:
			Node*					m_head;
//			os::critical_section	m_hLock;

			Node*					m_tail;
//			os::critical_section	m_tLock;

		};
	}
}
