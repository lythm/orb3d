#pragma once


namespace engine
{
	class DataStream
	{
	public:

		virtual uint64								Read(void* buffer, uint64 bytes)				= 0;
		virtual void								Seek(uint64 offset)								= 0;
		virtual void								Close()											= 0;
		virtual uint64								Size()											= 0;
		virtual uint64								Pos()											= 0;

	protected:
		DataStream(void)
		{
		}

		virtual ~DataStream(void)
		{
		}
	};


}
