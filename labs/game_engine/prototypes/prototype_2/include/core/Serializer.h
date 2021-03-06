#pragma once


#include "core/core_types.h"

namespace engine
{
	class Serializer
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