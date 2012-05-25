#pragma once

#include "core\Serializer.h"

namespace engine
{

	class ModelSerializer : public Serializer
	{
	public:
		
		virtual bool								Read(ModelPtr pModel)			= 0;
		virtual bool								Write(ModelPtr pModel)			= 0;

	protected:
		ModelSerializer(DataStreamPtr pStream) : Serializer(pStream){}
		virtual ~ModelSerializer(void){}
	};


}
