#pragma once

#include "core\Serializer.h"

namespace engine
{
	class MeshSerializer : public Serializer
	{
	public:

		virtual bool								Read(MeshPtr pMesh)				= 0;
		virtual bool								Write(MeshPtr pMesh)			= 0;

	protected:

		MeshSerializer(DataStreamPtr pStream) : Serializer(pStream){}

		virtual ~MeshSerializer(void){}
	};
}
