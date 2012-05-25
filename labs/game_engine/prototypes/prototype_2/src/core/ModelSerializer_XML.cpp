#include "core_pch.h"
#include "..\..\include\core\ModelSerializer_XML.h"


namespace engine
{
	ModelSerializer_XML::ModelSerializer_XML(DataStreamPtr pStream) : ModelSerializer(pStream)
	{
	}


	ModelSerializer_XML::~ModelSerializer_XML(void)
	{
	}
	
	bool ModelSerializer_XML::Read(ModelPtr pModel)
	{
		return true;
	}
	bool ModelSerializer_XML::Write(ModelPtr pModel)
	{
		return true;
	}
}