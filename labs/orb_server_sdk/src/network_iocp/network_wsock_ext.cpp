#include "network_pch.h"
#include "network_wsock_ext.h"

namespace orb
{
	namespace network
	{
		LPFN_ACCEPTEX										wsock_ext::ms_pfnAcceptEx							= NULL;
		LPFN_GETACCEPTEXSOCKADDRS							wsock_ext::ms_pfnGetAcceptExSockaddrs				= NULL;
		LPFN_CONNECTEX										wsock_ext::ms_pfnConnectEx							= NULL;
		LPFN_DISCONNECTEX									wsock_ext::ms_pfnDisconnectEx						= NULL;

		wsock_ext::wsock_ext(void)
		{
		}

		wsock_ext::~wsock_ext(void)
		{
		}

		void wsock_ext::UnloadExt()
		{
			ms_pfnAcceptEx							= NULL;
			ms_pfnGetAcceptExSockaddrs				= NULL;
			ms_pfnConnectEx							= NULL;
			ms_pfnDisconnectEx						= NULL;
		}
		bool wsock_ext::LoadExt()
		{
			SOCKET	s = socket(AF_INET, SOCK_STREAM, 0);
			DWORD dwBytes = 0;

			if(ms_pfnAcceptEx == NULL)
			{
				GUID extId = WSAID_ACCEPTEX;
				int ret = WSAIoctl(s, 
					SIO_GET_EXTENSION_FUNCTION_POINTER, 
					&extId, 
					sizeof(extId),
					&ms_pfnAcceptEx, 
					sizeof(ms_pfnAcceptEx), 
					&dwBytes, 
					NULL, 
					NULL);

				if(ret != 0)
				{
					closesocket(s);
					return false;
				}
			}
			if(ms_pfnGetAcceptExSockaddrs == NULL)
			{
				GUID extId = WSAID_GETACCEPTEXSOCKADDRS;

				int ret = WSAIoctl(s, 
					SIO_GET_EXTENSION_FUNCTION_POINTER, 
					&extId, 
					sizeof(extId),
					&ms_pfnGetAcceptExSockaddrs, 
					sizeof(ms_pfnGetAcceptExSockaddrs), 
					&dwBytes, 
					NULL, 
					NULL);

				if(ret != 0)
				{
					closesocket(s);
					return false;
				}
			}
			if(ms_pfnConnectEx == NULL)
			{
				GUID extId = WSAID_CONNECTEX;

				int ret = WSAIoctl(s, 
					SIO_GET_EXTENSION_FUNCTION_POINTER, 
					&extId, 
					sizeof(extId),
					&ms_pfnConnectEx, 
					sizeof(ms_pfnConnectEx), 
					&dwBytes, 
					NULL, 
					NULL);

				if(ret != 0)
				{
					closesocket(s);
					return false;
				}
			}
			if(ms_pfnDisconnectEx == NULL)
			{
				GUID extId = WSAID_DISCONNECTEX;

				int ret = WSAIoctl(s, 
					SIO_GET_EXTENSION_FUNCTION_POINTER, 
					&extId, 
					sizeof(extId),
					&ms_pfnDisconnectEx, 
					sizeof(ms_pfnDisconnectEx), 
					&dwBytes, 
					NULL, 
					NULL);

				if(ret != 0)
				{
					closesocket(s);
					return false;
				}
			}


			closesocket(s);
			return true;
		}


		BOOL wsock_ext::AcceptEx( SOCKET sListenSocket,
			SOCKET sAcceptSocket,
			PVOID lpOutputBuffer,
			DWORD dwReceiveDataLength,
			DWORD dwLocalAddressLength,
			DWORD dwRemoteAddressLength,
			LPDWORD lpdwBytesReceived,
			LPOVERLAPPED lpOverlapped)
		{
			return ms_pfnAcceptEx(sListenSocket,
				sAcceptSocket,
				lpOutputBuffer,
				dwReceiveDataLength,
				dwLocalAddressLength,
				dwRemoteAddressLength,
				lpdwBytesReceived,
				lpOverlapped);
		}

		VOID wsock_ext::GetAcceptExSockaddrs ( IN PVOID lpOutputBuffer,
			IN DWORD dwReceiveDataLength,
			IN DWORD dwLocalAddressLength,
			IN DWORD dwRemoteAddressLength,
			OUT struct sockaddr **LocalSockaddr,
			OUT LPINT LocalSockaddrLength,
			OUT struct sockaddr **RemoteSockaddr,
			OUT LPINT RemoteSockaddrLength)
		{
			return ms_pfnGetAcceptExSockaddrs(lpOutputBuffer,
				dwReceiveDataLength,
				dwLocalAddressLength,
				dwRemoteAddressLength,
				LocalSockaddr,
				LocalSockaddrLength,
				RemoteSockaddr,
				RemoteSockaddrLength);
		}

		BOOL wsock_ext::ConnectEx( IN SOCKET s,
			IN const struct sockaddr FAR *name,
			IN int namelen,
			IN PVOID lpSendBuffer OPTIONAL,
			IN DWORD dwSendDataLength,
			OUT LPDWORD lpdwBytesSent,
			IN LPOVERLAPPED lpOverlapped)
		{
			return ms_pfnConnectEx(s,
				name,
				namelen,
				lpSendBuffer,
				dwSendDataLength,
				lpdwBytesSent,
				lpOverlapped);
		}

		BOOL wsock_ext::DisconnectEx( IN SOCKET s,
			IN LPOVERLAPPED lpOverlapped,
			IN DWORD  dwFlags,
			IN DWORD  dwReserved)
		{
			return ms_pfnDisconnectEx(s, lpOverlapped, dwFlags, dwReserved);
		}

	}
}