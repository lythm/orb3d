#pragma once

#include <core/modelserializer.h>


namespace engine
{
	class ModelSerializer_Binary : public ModelSerializer
	{
	public:
		ModelSerializer_Binary(DataStreamPtr pStream);
		virtual ~ModelSerializer_Binary(void);

		bool								Read(ModelPtr pModel);
		bool								Write(ModelPtr pModel);
	};


}
