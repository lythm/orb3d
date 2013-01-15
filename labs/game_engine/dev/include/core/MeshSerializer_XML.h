#pragma once

#include "core\MeshSerializer.h"

namespace ld3d
{
	class MeshSerializer_XML : public MeshSerializer
	{
	public:
		MeshSerializer_XML(DataStreamPtr pStream);
		virtual ~MeshSerializer_XML(void);

		bool								Read(MeshPtr pMesh);
		bool								Write(MeshPtr pMesh);
	};


}