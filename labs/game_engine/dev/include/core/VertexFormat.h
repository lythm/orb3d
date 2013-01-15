#pragma once

#include "core\g_format.h"

namespace ld3d
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

	class VertexFormat
	{
	public:
		VertexFormat(){}
		
		void							SetElement(VertexElement e[], int c)
		{
			Clear();
			for(int i = 0; i < c; ++i)
			{
				AddElement(e[i]);
			}
		}
		void							AddElement(const VertexElement& e)
		{
			elems.push_back(e);
		}
		void							Clear()
		{
			elems.clear();
		}
		int								GetElementCount() const
		{
			return (int)elems.size();
		}

		const VertexElement&			GetElement(int index) const
		{
			return elems[index];
		}


	private:
		std::vector<VertexElement>		elems;
	};
}