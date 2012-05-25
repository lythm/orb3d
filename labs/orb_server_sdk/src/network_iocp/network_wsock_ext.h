#pragma once


namespace orb
{
	namespace network
	{
		class wsock_ext
		{
		public:
			static BOOL AcceptEx( SOCKET sListenSocket,
				SOCKET sAcceptSocket,
				PVOID lpOutputBuffer,
				DWORD dwReceiveDataLength,
				DWORD dwLocalAddressLength,
				DWORD dwRemoteAddressLength,
				LPDWORD lpdwBytesReceived,
				LPOVERLAPPED lpOverlapped);


			static VOID GetAcceptExSockaddrs ( IN PVOID lpOutputBuffer,
				IN DWORD dwReceiveDataLength,
				IN DWORD dwLocalAddressLength,
				IN DWORD dwRemoteAddressLength,
				OUT struct sockaddr **LocalSockaddr,
				OUT LPINT LocalSockaddrLength,
				OUT struct sockaddr **RemoteSockaddr,
				OUT LPINT RemoteSockaddrLength);

			static BOOL ConnectEx( IN SOCKET s,
				IN const struct sockaddr FAR *name,
				IN int namelen,
				IN PVOID lpSendBuffer OPTIONAL,
				IN DWORD dwSendDataLength,
				OUT LPDWORD lpdwBytesSent,
				IN LPOVERLAPPED lpOverlapped);

			static BOOL DisconnectEx( IN SOCKET s,
				IN LPOVERLAPPED lpOverlapped,
				IN DWORD  dwFlags,
				IN DWORD  dwReserved);

			static bool	LoadExt();

			static void UnloadExt();

		private:
			static LPFN_ACCEPTEX										ms_pfnAcceptEx;
			static LPFN_GETACCEPTEXSOCKADDRS							ms_pfnGetAcceptExSockaddrs;
			static LPFN_CONNECTEX										ms_pfnConnectEx;
			static LPFN_DISCONNECTEX									ms_pfnDisconnectEx;
		private:
			wsock_ext(void);
			~wsock_ext(void);
		};


	}
}