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

		Version(uint8 v1, uint8 v2, uint8 v3, uint8 v4)
		{
			Compose(v1, v2, v3, v4);
		}
		~Version(void){}


		void						Compose(uint8 v1, uint8 v2, uint8 v3, uint8 v4)
		{
			m_value = v1 <<24 | v2 << 16 | v3 << 8 | v4;
		}

		uint8						V1()
		{
			return m_value >> 24 & 0xffffff00;
		}
		uint8						V2()
		{
			return m_value >> 16 & 0xffffff00;
		}
		uint8						V3()
		{
			return m_value >> 8 & 0xffffff00;
		}
		uint8						V4()
		{
			return m_value & 0xffffff00;
		}

		void						V1(uint8 v)
		{
			m_value = m_value & 0x00ffffff | v << 24;
		}
		void						V2(uint8 v)
		{
			m_value = m_value & 0xff00ffff | v << 16;
		}
		void						V3(uint8 v)
		{
			m_value = m_value & 0xffff00ff | v << 8;
		}
		void						V4(uint8 v)
		{
			m_value = m_value & 0xffffff00 | v;
		}

		std::string					AsString()
		{
			char buffer[100];
			sprintf_s(buffer, 100, "%d.%d.%d.%d", V1(), V2(), V3(), V4());
			return buffer;
		}

		std::wstring				AsWString()
		{
			wchar_t buffer[100];
			swprintf_s(buffer, 100, L"%d.%d.%d.%d", V1(), V2(), V3(), V4());
			return buffer;
		}


		uint32						AsUInt32()
		{
			return m_value;
		}

	private:
		uint32						m_value;
	};


}
