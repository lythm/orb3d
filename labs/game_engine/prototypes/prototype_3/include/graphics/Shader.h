#pragma once
#include "graphics\VertexFormat.h"

namespace engine
{
	class Shader
	{
	public:

		virtual bool							LoadFromFile(const char* szFile)						= 0;

		virtual void							Release()												= 0;


		virtual void							SetVertexFormat(VertexElement format[], uint32 nElem)	= 0;
	protected:

		Shader(void){}

		virtual ~Shader(void){}
	};


}