#pragma once
namespace engine
{
	class VoxelWorldSerializer : public Serializer
	{
	public:
		VoxelWorldSerializer(DataStreamPtr pStream);
		virtual ~VoxelWorldSerializer(void);
	};

	class VoxelEntitySerializer
	{
		VoxelEntitySerializer(void);
		virtual ~VoxelEntitySerializer(void);
	};
}