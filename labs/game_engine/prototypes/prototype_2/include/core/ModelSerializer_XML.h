#pragma once

#include "core/ModelSerializer.h"

namespace engine
{
	class ModelSerializer_XML : public ModelSerializer
	{
	public:
		ModelSerializer_XML(DataStreamPtr pStream);
		virtual ~ModelSerializer_XML(void);

		
		bool								Read(ModelPtr pModel);
		bool								Write(ModelPtr pModel);

	};


}