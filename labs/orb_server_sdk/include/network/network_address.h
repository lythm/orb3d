#pragma once

#include "network_types.h"

#include <string>

#include <boost/lexical_cast.hpp>

namespace orb
{
	namespace network
	{
		struct IPAddress
		{
			///The peer address from inet_addr.
			uint32 binaryAddress;
			///The port number
			uint16 port;


			static IPAddress AnyAddress()
			{
				IPAddress addr;
				addr.binaryAddress = 0;
				addr.port = 0;
			}

			static IPAddress InvalidAddress()
			{
				return IPAddress();
			}

			static IPAddress ParseAddress(const char* szAddr)
			{
				IPAddress addr;
				addr.Parse(szAddr);
				return addr;
			}

			IPAddress()
			{
				binaryAddress	= 0xffffffff;
				port			= 0xffff;
			}

			IPAddress(const char* szAddr)
			{
				Parse(szAddr);
			}

			IPAddress(const IPAddress& other)
			{
				*this = other;
			}

			// Return the systemAddress as a string in the format <IP>:<Port>
			// dest must be large enough to hold the output
			// THREADSAFE
			std::string ToString(bool writePort = true) const
			{
				in_addr in;
				in.s_addr = binaryAddress;

				std::string addr = inet_ntoa( in );

				if (writePort)
				{
					addr += ":";
					addr += boost::lexical_cast<std::string>(port);
				}

				return addr;
			}

			bool Parse(const char *str)
			{
				if (str[0]<'0' || str[0]>'9')
				{
					return false;
				}

				// Split the string into the first part, and the : part
				uint32 index, portIndex;
				char IPPart[22];
				char portPart[10];

				// Only write the valid parts, don't change existing if invalid
				//	binaryAddress=UNASSIGNED_IPADDRESS.binaryAddress;
				//	port=UNASSIGNED_IPADDRESS.port;

				for (index=0; str[index] && str[index]!=':' && index< 22; index++)
				{
					IPPart[index]=str[index];
				}
				IPPart[index]=0;
				portPart[0]=0;
				if (str[index] && str[index+1])
				{
					index++;
					for (portIndex=0; portIndex<10 && str[index] && index < 22+10; index++, portIndex++)
						portPart[portIndex]=str[index];
					portPart[portIndex]=0;
				}


				if (IPPart[0])
				{
					binaryAddress=inet_addr(IPPart);
				}

				if(binaryAddress == INADDR_NONE)
					return false;

				if (portPart[0])
					port=(unsigned short) atoi(portPart);


				return true;
			}

			IPAddress& operator = ( const IPAddress& input )
			{
				if(this == &input)
				{
					return *this;
				}

				binaryAddress = input.binaryAddress;
				port = input.port;
				return *this;
			}

			bool operator==( const IPAddress& right ) const
			{
				return binaryAddress == right.binaryAddress && port == right.port;
			}

			bool operator!=( const IPAddress& right ) const
			{
				return binaryAddress != right.binaryAddress || port != right.port;
			}
		};
	}
}
