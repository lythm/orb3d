#pragma once

#include "core\g_format.h"

namespace engine
{
	class VertexElement
	{
	public:

		enum SEMANTIC
		{
			POSITION,
			NORMAL,
			COLOR,
			TEXCOORD,
			POSITION_T,
		};


		VertexElement(int i, SEMANTIC s, G_FORMAT t)
		{
			type = t;
			semantic = s;
			element_slot = i;
		}

		G_FORMAT						type;
		SEMANTIC						semantic;
		int								element_slot;
	};

}