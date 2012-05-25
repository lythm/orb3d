#include "core_pch.h"
#include "..\..\include\core\Mesh.h"


namespace engine
{
	Mesh::Mesh(void)
	{
	}


	Mesh::~Mesh(void)
	{
	}
	unsigned int Mesh::GetRenderDataCount()
	{
		return 0;
	}
	RenderDataPtr Mesh::GetRenderData(unsigned int index)
	{
		return RenderDataPtr();
	}
}
