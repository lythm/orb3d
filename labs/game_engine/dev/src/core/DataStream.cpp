#include "core_pch.h"
#include "core\DataStream.h"
#include "core_utils.h"

namespace ld3d
{
	DataStream::DataStream(void)
	{
	}

	DataStream::~DataStream(void)
	{

	}
	void DataStream::ReadString(std::wstring& str)
	{
		uint16 len = 0;

		Read(&len, sizeof(uint16));
		
		if(len == 0)
		{
			str = L"";
			return;
		}
		wchar_t* buffer = (wchar_t*)mem_alloc((len + 1) * sizeof(uint16));

		Read(buffer, len * sizeof(uint16));
		buffer[len] = 0;
		str = buffer;

		mem_free(buffer);

	}
	void DataStream::WriteString(const std::wstring& str)
	{
		uint16 len = str.length();
		const wchar_t* buffer = str.c_str();

		Write(&len, sizeof(uint16));

		if(len == 0)
		{
			return;
		}
		Write((void*)buffer, len * sizeof(uint16));
	}

	void DataStream::ReadString(std::string& str)
	{
		uint16 len = 0;

		Read(&len, sizeof(uint16));
		
		char* buffer = (char*)mem_alloc(len);

		Read(buffer, len);

		str = buffer;

		mem_free(buffer);

	}
	void DataStream::WriteString(const std::string& str)
	{
		uint16 len = str.length();
		const char* buffer = str.c_str();

		Write(&len, sizeof(uint16));
		Write((void*)buffer, len);
	}

	uint8 DataStream::ReadInt8()
	{
		uint8 v = 0;
		Read(&v, sizeof(uint8));

		return v;
	}
	void DataStream::WriteInt8(uint8 v)
	{
		Write(&v, sizeof(uint8));
	}

	bool DataStream::ReadBool()
	{
		bool v = 0;
		Read(&v, sizeof(bool));

		return v;
	}
	void DataStream::WriteBool(bool v)
	{
		Write(&v, sizeof(bool));
	}

	uint16 DataStream::ReadInt16()
	{
		uint16 v = 0;
		Read(&v, sizeof(uint16));

		return v;
	}
	void DataStream::WriteInt16(uint16 v)
	{
		Write(&v, sizeof(uint16));
	}

	uint32 DataStream::ReadInt32()
	{
		uint32 v = 0;
		Read(&v, sizeof(uint32));

		return v;
	}
	void DataStream::WriteInt32(uint32 v)
	{
		Write(&v, sizeof(uint32));
	}

	uint64 DataStream::ReadInt64()
	{
		uint64 v = 0;
		Read(&v, sizeof(uint64));

		return v;
	}
	void DataStream::WriteInt64(uint64 v)
	{
		Write(&v, sizeof(uint64));
	}

	float DataStream::ReadFloat32()
	{
		float v = 0;
		Read(&v, sizeof(float));

		return v;
	}
	void DataStream::WriteFloat32(float v)
	{
		Write(&v, sizeof(float));
	}

	double DataStream::ReadFloat64()
	{
		double v = 0;
		Read(&v, sizeof(double));

		return v;
	}

	void DataStream::WriteFloat64(double v)
	{
		Write(&v, sizeof(double));
	}
}
