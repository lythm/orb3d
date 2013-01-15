#include "core_pch.h"
#include "..\..\include\core\MeshSerializer_XML.h"

namespace ld3d
{
	MeshSerializer_XML::MeshSerializer_XML(DataStreamPtr pStream) : MeshSerializer(pStream)
	{
	}


	MeshSerializer_XML::~MeshSerializer_XML(void)
	{
	}
	bool MeshSerializer_XML::Read(MeshPtr pMesh)
	{
		return true;
	}
	bool MeshSerializer_XML::Write(MeshPtr pMesh)
	{
		return true;
	}
}
