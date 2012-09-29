#pragma once


namespace engine
{
	class VertexElement
	{
	public:

		enum ELEMENT_TYPE
		{
			VE_FLOAT4,
			VE_FLOAT3,
			VE_FLOAT2,
			VE_FLOAT1,

			VE_UINT32,

		};

		enum SEMANTIC
		{
			POSITION,
			NORMAL,
			COLOR,
			TEXCOORD,
			POSITION_T,
		};


		VertexElement(int i, SEMANTIC s, ELEMENT_TYPE t)
		{
			type = t;
			semantic = s;
			element_slot = i;
		}

		ELEMENT_TYPE					type;
		SEMANTIC						semantic;
		int								element_slot;
	};

}