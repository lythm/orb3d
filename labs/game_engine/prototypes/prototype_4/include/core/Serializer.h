#pragma once




namespace engine
{
	class EXPORT_CLASS Serializer
	{
	protected:
		Serializer(DataStreamPtr pStream)
		{
			m_pStream = pStream;
		}
		virtual ~Serializer(void)
		{
			m_pStream.reset();
		}




	protected:
		DataStreamPtr										m_pStream;
	};
}
