#pragma once

#include "core\MeshSerializer.h"

namespace engine
{
	class MeshSerializer_XML : public MeshSerializer
	{
	public:
		MeshSerializer_XML(DataStreamPtr pStream);
		virtual ~MeshSerializer_XML(void);
	};


}