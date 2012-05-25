#pragma once


namespace engine
{
	class GeometryBuffer
	{
	public:

		enum MAP_HINT
		{
			MAP_DEFAULT,
			MAP_DISCARD,
			MAP_NO_OVERWRITE,

		};


		virtual bool											AllocVertexBuffer(unsigned int bytes, bool dynamic = false)												= 0;
		virtual void											FreeVertexBuffer()																						= 0;

		virtual bool											AllocIndexBuffer(unsigned int bytes, bool dynamic = false)												= 0;
		virtual void											FreeIndexBuffer()																						= 0;

		virtual void*											MapVertexBuffer(MAP_HINT hint)																			= 0;
		virtual void											UnmapVertexBuffer()																						= 0;

		virtual void*											MapIndexBuffer(MAP_HINT hint)																			= 0;
		virtual void											UnmapIndexBuffer()																						= 0;
		
		virtual void											Apply(uint32 vertexBufferoffset, uint32 vertexBufferstride, uint32 indexBufferOffset)					= 0;

		virtual void											Apply(uint32 vertexStride)																				= 0;

	protected:

		GeometryBuffer(void)
		{
		}

		virtual ~GeometryBuffer(void)
		{
		}
	};
}
