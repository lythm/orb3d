#pragma once

#include "types\types.h"
#include <string>

namespace ld3d
{
	class Version
	{
	public:
		Version(void)
		{
			m_value = 0;
		}
		Version(uint32 v)
		{
			FromUInt32(v);
		}

		Version(uint8 v1, uint8 v2, uint8 v3, uint8 v4)
		{
			Compose(v1, v2, v3, v4);
		}

		Version(const Version& v)
		{
			*this = v;
		}

		~Version(void){}

		void						FromUInt32(uint32 v)
		{
			m_value = v;
		}
		void						Compose(uint8 v1, uint8 v2, uint8 v3, uint8 v4)
		{
			m_value = v1 <<24 | v2 << 16 | v3 << 8 | v4;
		}

		uint8						V1() const
		{
			return m_value >> 24 & 0x000000ff;
		}
		uint8						V2() const
		{
			return m_value >> 16 & 0x000000ff;
		}
		uint8						V3() const
		{
			return m_value >> 8 & 0x000000ff;
		}
		uint8						V4() const
		{
			return m_value & 0x000000ff;
		}

		void						V1(uint8 v)
		{
			m_value = (m_value & 0x00ffffff) | (v << 24);
		}
		void						V2(uint8 v)
		{
			m_value = (m_value & 0xff00ffff) | (v << 16);
		}
		void						V3(uint8 v)
		{
			m_value = (m_value & 0xffff00ff) | (v << 8);
		}
		void						V4(uint8 v)
		{
			m_value = (m_value & 0xffffff00) | v;
		}

		std::string					AsString() const
		{
			char buffer[100];
			sprintf_s(buffer, 100, "%d.%d.%d.%d", V1(), V2(), V3(), V4());
			return buffer;
		}

		std::wstring				AsWString() const
		{
			wchar_t buffer[100];
			swprintf_s(buffer, 100, L"%d.%d.%d.%d", V1(), V2(), V3(), V4());
			return buffer;
		}


		uint32						AsUInt32() const
		{
			return m_value;
		}


		bool						operator ==(const Version& rhs) const
		{
			return m_value == rhs.m_value;
		}
		bool						operator !=(const Version& rhs) const
		{
			return operator==(rhs) == false;
		}
		const Version&				operator=(const Version& rhs)
		{
			if(this != &rhs)
			{
				m_value = rhs.m_value;
			}
			
			return *this;
		}
	private:
		uint32						m_value;
	};


}
