#include "core_pch.h"
#include "..\..\include\core\ModelSerializer_Binary.h"


namespace engine
{
	ModelSerializer_Binary::ModelSerializer_Binary(DataStreamPtr pStream) : ModelSerializer(pStream)
	{
	}


	ModelSerializer_Binary::~ModelSerializer_Binary(void)
	{
	}
	

	bool ModelSerializer_Binary::Read(ModelPtr pModel)
	{
		return true;
	}
	bool ModelSerializer_Binary::Write(ModelPtr pModel)
	{
		return true;
	}
}
