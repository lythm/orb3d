#pragma once

#include "types\types.h"

namespace ld3d
{
	class EXPORT_CLASS DataStream
	{
	public:

		virtual uint64								Read(void* buffer, uint64 bytes)				= 0;
		virtual uint64								Write(void* buffer, uint64 bytes)				= 0;
		virtual void								Seek(uint64 offset)								= 0;
		virtual void								Close()											= 0;
		virtual uint64								Size()											= 0;
		virtual uint64								Pos()											= 0;
		
		
		void										ReadString(std::wstring& str);
		void										WriteString(const std::wstring& str);

		void										ReadString(std::string& str);
		void										WriteString(const std::string& str);

		uint8										ReadInt8();
		void										WriteInt8(uint8 v);

		bool										ReadBool();
		void										WriteBool(bool v);

		uint16										ReadInt16();
		void										WriteInt16(uint16 v);

		uint32										ReadInt32();
		void										WriteInt32(uint32 v);

		uint64										ReadInt64();
		void										WriteInt64(uint64 v);

		float										ReadFloat32();
		void										WriteFloat32(float v);

		double										ReadFloat64();
		void										WriteFloat64(double v);

	protected:
		DataStream(void);
		virtual ~DataStream(void);
	};


}
