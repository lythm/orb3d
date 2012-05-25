#include "network_pch.h"
#include "network_Network_iocp.h"
#include "network_wsock_ext.h"
#include <process.h>
#include <ObjBase.h>

namespace orb
{
	namespace network
	{
		_DLL_API Device* AllocDevice()
		{
			return new Network_iocp;
		}
		_DLL_API void FreeDevice(Device* pDevice)
		{

			delete (Network_iocp*)pDevice;
		}
	}
}





namespace orb
{
	namespace network
	{
		Network_iocp::Network_iocp(void)
		{
			m_pIOCP				= NULL;

		}


		Network_iocp::~Network_iocp(void)
		{
			m_threads.clear();
		}

		const w_char* Network_iocp::GetName()
		{
			return L"IOCP Network Device";
		}

		bool Network_iocp::Initialize(DeviceHost* pHost)
		{
			uint16 nThread = _wtoi(pHost->AppSettings(L"device_network_threads", 0).c_str());

			if(initialize_network(nThread) != ret_ok)
				return false;

			return true;
		}
		void Network_iocp::Release()
		{
			release_network();
		}
		Network_iocp::Result Network_iocp::initialize_network(uint16 n_threads)
		{

			CoInitializeEx(NULL, COINIT_MULTITHREADED);
			WSADATA wsaData;
			if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
			{
				return ret_failed;
			}

			if(false == wsock_ext::LoadExt())
			{
				return ret_failed_to_load_wsock_ext;
			}

			m_pIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, n_threads);
			if(m_pIOCP == NULL)
				return ret_failed;

			if(n_threads == 0)
			{
				SYSTEM_INFO info;
				GetSystemInfo(&info);

				n_threads = info.dwNumberOfProcessors * 2;
			}

			for(uint16 i = 0; i < n_threads; ++i)
			{
				HANDLE hThread = (HANDLE)_beginthreadex(0, 0, iocp_handler, (void*)this, 0, 0);
				if(hThread == 0)
					return ret_failed_to_create_thread_pool;
				m_threads.push_back(hThread);
			}

			return ret_ok;
		}
		void Network_iocp::release_network()
		{
			for(size_t i = 0; i < m_threads.size(); ++i)
			{
				PostQueuedCompletionStatus(m_pIOCP, 0, 0, 0);
			}

			for(size_t i = 0; i < m_threads.size(); ++i)
			{
				HANDLE id = (HANDLE)m_threads[i];
				DWORD dwRet = WaitForSingleObject(id, 1000000);

				switch( dwRet )
				{
				case WAIT_FAILED:
				case WAIT_TIMEOUT:
					TerminateThread(id, DWORD(-99));
					break;
				default:
					break;
				}
				CloseHandle(id);
			}

			m_threads.clear();

			if(m_pIOCP)
			{
				CloseHandle(m_pIOCP);
				m_pIOCP = NULL;
			}
			
			wsock_ext::UnloadExt();

			WSACleanup();
			CoUninitialize();
		}

		Network_iocp::Result Network_iocp::aio_read(aio_op* op)
		{
			if(op == NULL)
				return ret_bad_call;

			if(op->handler == NULL)
				return ret_bad_call;

			if(op->buffer == NULL)
				return ret_bad_call;

			op->_private_data.buffer.buf = (char*)op->buffer;
			op->_private_data.buffer.len = op->buffer_bytes;

			op->op = aio_op::op_read;
			op->data_transfered = 0;
			
			DWORD dwRecv;
			DWORD dwFlag = 0;

			int ret = WSARecv((SOCKET)op->s, &op->_private_data.buffer, 1, &dwRecv, &dwFlag, &op->_private_data.ol, NULL);
			DWORD dwError = WSAGetLastError();
			if(ret != 0)
			{
				if(dwError != WSA_IO_PENDING)
				{
					return ret_failed;
				}
			}
			
			return ret_ok;
		}

		Network_iocp::Result Network_iocp::aio_write(aio_op* op)
		{
			if(op == NULL)
				return ret_bad_call;

			if(op->handler == NULL)
				return ret_bad_call;

			if(op->buffer == NULL)
				return ret_bad_call;

			op->_private_data.buffer.buf = (char*)op->buffer;
			op->_private_data.buffer.len = op->buffer_bytes;

			op->op = aio_op::op_write;

			op->data_transfered = 0;

			DWORD dwBytes = 0;
			int ret = WSASend((SOCKET)op->s, &op->_private_data.buffer, 1, &dwBytes, 0, &op->_private_data.ol, 0);
			DWORD error = WSAGetLastError();
			if(ret != 0)
			{
				if(error != WSA_IO_PENDING)
					return ret_failed;
			}
			return ret_ok;
		}

		Network_iocp::Result Network_iocp::aio_disconnect(aio_op* op, bool reuse_sock)
		{
			if(op == NULL)
				return ret_bad_call;

			if(op->handler == NULL)
				return ret_bad_call;

		
			op->op = aio_op::op_disconnect;

			int ret = wsock_ext::DisconnectEx(op->s, &op->_private_data.ol, reuse_sock ? TF_REUSE_SOCKET : 0, 0);
			DWORD error = WSAGetLastError();
			if(ret == FALSE)
			{
				if(error != WSA_IO_PENDING)
					return ret_failed;
			}

			return ret_ok;
		}


		Network_iocp::Result Network_iocp::aio_connect(aio_op* op, const IPAddress& addr)
		{
			if(op == NULL)
				return ret_bad_call;

			if(op->handler == NULL)
				return ret_bad_call;

		
			op->op = aio_op::op_connect;
			
			struct sockaddr_in sock_addr;
			sock_addr.sin_family = AF_INET;
			sock_addr.sin_port = ntohs(addr.port);
			sock_addr.sin_addr.S_un.S_addr = addr.binaryAddress;

			DWORD dwBytes = 0;
			int ret = wsock_ext::ConnectEx(op->s, (sockaddr *)&sock_addr, sizeof(sock_addr), NULL, 0, &dwBytes, &op->_private_data.ol);
			DWORD error = WSAGetLastError();
			if(ret == FALSE)
			{
				if(error != WSA_IO_PENDING)
					return ret_failed;
			}

			return ret_ok;
		}

		Network_iocp::Result Network_iocp::aio_accept(sock listener_sock, aio_op* op)
		{
			if(op == NULL)
				return ret_bad_call;

			if(op->handler == NULL)
			{
				return ret_bad_call;
			}

			if(op->buffer == NULL || op->buffer_bytes < (sizeof(SOCKADDR_IN) + 16) * 2)
			{
				return ret_bad_call;
			}
			if(op->s == NULL)
			{
				op->s = socket();
			}

			op->op = aio_op::op_accept;
			
			DWORD dwBytes = 0;
			if(FALSE == wsock_ext::AcceptEx((SOCKET)listener_sock, (SOCKET)op->s, op->buffer, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwBytes, &op->_private_data.ol))
			{
				DWORD dwErr = WSAGetLastError();
				if(dwErr !=  ERROR_IO_PENDING)
				{
					return ret_failed;
				}
			}
			
			return ret_ok;
		}

		Network_iocp::Result Network_iocp::aio_cancel(sock s)
		{

			return ret_ok;
			//return CancelIoEx((HANDLE)s, NULL) ? ret_ok : ret_failed;
		}

		sock Network_iocp::socket()
		{
			SOCKET s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
			
			if(s == INVALID_SOCKET)
				return invalid_sock;

			if(NULL == CreateIoCompletionPort((HANDLE)s, m_pIOCP, (ULONG_PTR)&s, 0))
			{
				::closesocket(s);
				return invalid_sock;
			}

			return (sock)s;
		}
		Network_iocp::Result Network_iocp::bind(sock s, const IPAddress& addr)
		{
			struct sockaddr_in localAddr;
			localAddr.sin_family = AF_INET;
			localAddr.sin_port = ntohs(addr.port);

			localAddr.sin_addr.S_un.S_addr = addr.binaryAddress;
			

			if(SOCKET_ERROR == ::bind(s, (sockaddr *)&localAddr, sizeof(localAddr)))
			{
				::closesocket(s);
				return ret_failed;
			}

			return ret_ok;
		}

		Network_iocp::Result Network_iocp::listen(sock s)
		{
			BOOL bval = TRUE;
			setsockopt((SOCKET)s, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&bval, sizeof(int));


			if(0 != ::listen((SOCKET)s, SOMAXCONN))
			{
				close(s);
				return ret_failed;
			}
			
			return ret_ok;
		}

		void Network_iocp::close(sock s)
		{
			closesocket((SOCKET)s);
		}

		unsigned int Network_iocp::iocp_handler(void* param)
		{
			Network_iocp*	pThis			= (Network_iocp*)param;
			HANDLE			hIocp			= pThis->m_pIOCP;

			aio_op*			op				= NULL;
			sock*			key				= NULL;

			while(true)
			{

				DWORD dwTrans		= 0;

				BOOL ret			= GetQueuedCompletionStatus(hIocp, &dwTrans, (LPDWORD)&key, (LPOVERLAPPED *)&op, WSA_INFINITE);

				DWORD  errCode		= GetLastError();

				if(key == NULL)
				{
					// quit normally
					return 0;
				}

				if(op == NULL)
				{
					assert(0);
					continue;
				}

				op->sock_error = errCode;
				op->data_transfered = dwTrans;
				op->result = aio_op::result_ok;
				
				if(ret == FALSE)
				{
					// falied io request
					if(errCode == ERROR_OPERATION_ABORTED)
					{
						op->result = aio_op::result_abort;
					}
					else
					{
						op->result = aio_op::result_failed;
					}
				}

				op->handler(op);

			}
			return -1;
		}
	}
}


