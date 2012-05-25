#pragma once

#include <boost\shared_ptr.hpp>

namespace engine
{
	enum DEVICE_MAP
	{
		DEVICE_MAP_READ                 = 1,
		DEVICE_MAP_WRITE                = 2,
		DEVICE_MAP_READ_WRITE           = 3,
		DEVICE_MAP_WRITE_DISCARD        = 4,
		DEVICE_MAP_WRITE_NO_OVERWRITE   = 5,
	};

	enum DEVICE_USAGE
	{
		USAGE_STATIC				= 0,
		USAGE_DYNAMIC				= 2,
	};

	enum DEVICE_CPU_ACCESS
	{
		CPU_ACCESS_WRITE			= 0x10000L,
		CPU_ACCESS_READ				= 0x20000L,
	};

	enum DEVICE_BINDING
	{
		BINDING_VERTEX_BUFFER,
		BINDING_INDEX_BUFFER,
		BINDING_CONSTANT_BUFFER,
	};

	enum DEVICE_FORMAT
	{
		DEVICE_FORMAT_UNKNOWN                      = 0,
		DEVICE_FORMAT_R32G32B32A32_TYPELESS        = 1,
		DEVICE_FORMAT_R32G32B32A32_FLOAT           = 2,
		DEVICE_FORMAT_R32G32B32A32_UINT            = 3,
		DEVICE_FORMAT_R32G32B32A32_SINT            = 4,
		DEVICE_FORMAT_R32G32B32_TYPELESS           = 5,
		DEVICE_FORMAT_R32G32B32_FLOAT              = 6,
		DEVICE_FORMAT_R32G32B32_UINT               = 7,
		DEVICE_FORMAT_R32G32B32_SINT               = 8,
		DEVICE_FORMAT_R16G16B16A16_TYPELESS        = 9,
		DEVICE_FORMAT_R16G16B16A16_FLOAT           = 10,
		DEVICE_FORMAT_R16G16B16A16_UNORM           = 11,
		DEVICE_FORMAT_R16G16B16A16_UINT            = 12,
		DEVICE_FORMAT_R16G16B16A16_SNORM           = 13,
		DEVICE_FORMAT_R16G16B16A16_SINT            = 14,
		DEVICE_FORMAT_R32G32_TYPELESS              = 15,
		DEVICE_FORMAT_R32G32_FLOAT                 = 16,
		DEVICE_FORMAT_R32G32_UINT                  = 17,
		DEVICE_FORMAT_R32G32_SINT                  = 18,
		DEVICE_FORMAT_R32G8X24_TYPELESS            = 19,
		DEVICE_FORMAT_D32_FLOAT_S8X24_UINT         = 20,
		DEVICE_FORMAT_R32_FLOAT_X8X24_TYPELESS     = 21,
		DEVICE_FORMAT_X32_TYPELESS_G8X24_UINT      = 22,
		DEVICE_FORMAT_R10G10B10A2_TYPELESS         = 23,
		DEVICE_FORMAT_R10G10B10A2_UNORM            = 24,
		DEVICE_FORMAT_R10G10B10A2_UINT             = 25,
		DEVICE_FORMAT_R11G11B10_FLOAT              = 26,
		DEVICE_FORMAT_R8G8B8A8_TYPELESS            = 27,
		DEVICE_FORMAT_R8G8B8A8_UNORM               = 28,
		DEVICE_FORMAT_R8G8B8A8_UNORM_SRGB          = 29,
		DEVICE_FORMAT_R8G8B8A8_UINT                = 30,
		DEVICE_FORMAT_R8G8B8A8_SNORM               = 31,
		DEVICE_FORMAT_R8G8B8A8_SINT                = 32,
		DEVICE_FORMAT_R16G16_TYPELESS              = 33,
		DEVICE_FORMAT_R16G16_FLOAT                 = 34,
		DEVICE_FORMAT_R16G16_UNORM                 = 35,
		DEVICE_FORMAT_R16G16_UINT                  = 36,
		DEVICE_FORMAT_R16G16_SNORM                 = 37,
		DEVICE_FORMAT_R16G16_SINT                  = 38,
		DEVICE_FORMAT_R32_TYPELESS                 = 39,
		DEVICE_FORMAT_D32_FLOAT                    = 40,
		DEVICE_FORMAT_R32_FLOAT                    = 41,
		DEVICE_FORMAT_R32_UINT                     = 42,
		DEVICE_FORMAT_R32_SINT                     = 43,
		DEVICE_FORMAT_R24G8_TYPELESS               = 44,
		DEVICE_FORMAT_D24_UNORM_S8_UINT            = 45,
		DEVICE_FORMAT_R24_UNORM_X8_TYPELESS        = 46,
		DEVICE_FORMAT_X24_TYPELESS_G8_UINT         = 47,
		DEVICE_FORMAT_R8G8_TYPELESS                = 48,
		DEVICE_FORMAT_R8G8_UNORM                   = 49,
		DEVICE_FORMAT_R8G8_UINT                    = 50,
		DEVICE_FORMAT_R8G8_SNORM                   = 51,
		DEVICE_FORMAT_R8G8_SINT                    = 52,
		DEVICE_FORMAT_R16_TYPELESS                 = 53,
		DEVICE_FORMAT_R16_FLOAT                    = 54,
		DEVICE_FORMAT_D16_UNORM                    = 55,
		DEVICE_FORMAT_R16_UNORM                    = 56,
		DEVICE_FORMAT_R16_UINT                     = 57,
		DEVICE_FORMAT_R16_SNORM                    = 58,
		DEVICE_FORMAT_R16_SINT                     = 59,
		DEVICE_FORMAT_R8_TYPELESS                  = 60,
		DEVICE_FORMAT_R8_UNORM                     = 61,
		DEVICE_FORMAT_R8_UINT                      = 62,
		DEVICE_FORMAT_R8_SNORM                     = 63,
		DEVICE_FORMAT_R8_SINT                      = 64,
		DEVICE_FORMAT_A8_UNORM                     = 65,
		DEVICE_FORMAT_R1_UNORM                     = 66,
		DEVICE_FORMAT_R9G9B9E5_SHAREDEXP           = 67,
		DEVICE_FORMAT_R8G8_B8G8_UNORM              = 68,
		DEVICE_FORMAT_G8R8_G8B8_UNORM              = 69,
		DEVICE_FORMAT_BC1_TYPELESS                 = 70,
		DEVICE_FORMAT_BC1_UNORM                    = 71,
		DEVICE_FORMAT_BC1_UNORM_SRGB               = 72,
		DEVICE_FORMAT_BC2_TYPELESS                 = 73,
		DEVICE_FORMAT_BC2_UNORM                    = 74,
		DEVICE_FORMAT_BC2_UNORM_SRGB               = 75,
		DEVICE_FORMAT_BC3_TYPELESS                 = 76,
		DEVICE_FORMAT_BC3_UNORM                    = 77,
		DEVICE_FORMAT_BC3_UNORM_SRGB               = 78,
		DEVICE_FORMAT_BC4_TYPELESS                 = 79,
		DEVICE_FORMAT_BC4_UNORM                    = 80,
		DEVICE_FORMAT_BC4_SNORM                    = 81,
		DEVICE_FORMAT_BC5_TYPELESS                 = 82,
		DEVICE_FORMAT_BC5_UNORM                    = 83,
		DEVICE_FORMAT_BC5_SNORM                    = 84,
		DEVICE_FORMAT_B5G6R5_UNORM                 = 85,
		DEVICE_FORMAT_B5G5R5A1_UNORM               = 86,
		DEVICE_FORMAT_B8G8R8A8_UNORM               = 87,
		DEVICE_FORMAT_B8G8R8X8_UNORM               = 88,
		DEVICE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
		DEVICE_FORMAT_B8G8R8A8_TYPELESS            = 90,
		DEVICE_FORMAT_B8G8R8A8_UNORM_SRGB          = 91,
		DEVICE_FORMAT_B8G8R8X8_TYPELESS            = 92,
		DEVICE_FORMAT_B8G8R8X8_UNORM_SRGB          = 93,
		DEVICE_FORMAT_BC6H_TYPELESS                = 94,
		DEVICE_FORMAT_BC6H_UF16                    = 95,
		DEVICE_FORMAT_BC6H_SF16                    = 96,
		DEVICE_FORMAT_BC7_TYPELESS                 = 97,
		DEVICE_FORMAT_BC7_UNORM                    = 98,
		DEVICE_FORMAT_BC7_UNORM_SRGB               = 99,
		DEVICE_FORMAT_FORCE_UINT                   = 0xffffffffUL 
	};


	struct RenderData;
	class GeometryBuffer;
	class RenderTarget;
	class FrameBuffer;
	class Texture;
	class GraphicsFX;


	typedef boost::shared_ptr<GraphicsFX>								GraphicsFXPtr;
	typedef boost::shared_ptr<Texture>									TexturePtr;
	typedef boost::shared_ptr<FrameBuffer>								FrameBufferPtr;
	typedef boost::shared_ptr<RenderTarget>								RenderTargetPtr;
	typedef boost::shared_ptr<RenderData>								RenderDataPtr;
	typedef boost::shared_ptr<GeometryBuffer>							GeometryBufferPtr;
}