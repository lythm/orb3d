#pragma once

namespace ld3d
{
	typedef enum G_FORMAT
	{
		G_FORMAT_UNKNOWN                      = 0,
		G_FORMAT_R32G32B32A32_TYPELESS        = 1,
		G_FORMAT_R32G32B32A32_FLOAT           = 2,
		G_FORMAT_R32G32B32A32_UINT            = 3,
		G_FORMAT_R32G32B32A32_SINT            = 4,
		G_FORMAT_R32G32B32_TYPELESS           = 5,
		G_FORMAT_R32G32B32_FLOAT              = 6,
		G_FORMAT_R32G32B32_UINT               = 7,
		G_FORMAT_R32G32B32_SINT               = 8,
		G_FORMAT_R16G16B16A16_TYPELESS        = 9,
		G_FORMAT_R16G16B16A16_FLOAT           = 10,
		G_FORMAT_R16G16B16A16_UNORM           = 11,
		G_FORMAT_R16G16B16A16_UINT            = 12,
		G_FORMAT_R16G16B16A16_SNORM           = 13,
		G_FORMAT_R16G16B16A16_SINT            = 14,
		G_FORMAT_R32G32_TYPELESS              = 15,
		G_FORMAT_R32G32_FLOAT                 = 16,
		G_FORMAT_R32G32_UINT                  = 17,
		G_FORMAT_R32G32_SINT                  = 18,
		G_FORMAT_R32G8X24_TYPELESS            = 19,
		G_FORMAT_D32_FLOAT_S8X24_UINT         = 20,
		G_FORMAT_R32_FLOAT_X8X24_TYPELESS     = 21,
		G_FORMAT_X32_TYPELESS_G8X24_UINT      = 22,
		G_FORMAT_R10G10B10A2_TYPELESS         = 23,
		G_FORMAT_R10G10B10A2_UNORM            = 24,
		G_FORMAT_R10G10B10A2_UINT             = 25,
		G_FORMAT_R11G11B10_FLOAT              = 26,
		G_FORMAT_R8G8B8A8_TYPELESS            = 27,
		G_FORMAT_R8G8B8A8_UNORM               = 28,
		G_FORMAT_R8G8B8A8_UNORM_SRGB          = 29,
		G_FORMAT_R8G8B8A8_UINT                = 30,
		G_FORMAT_R8G8B8A8_SNORM               = 31,
		G_FORMAT_R8G8B8A8_SINT                = 32,
		G_FORMAT_R16G16_TYPELESS              = 33,
		G_FORMAT_R16G16_FLOAT                 = 34,
		G_FORMAT_R16G16_UNORM                 = 35,
		G_FORMAT_R16G16_UINT                  = 36,
		G_FORMAT_R16G16_SNORM                 = 37,
		G_FORMAT_R16G16_SINT                  = 38,
		G_FORMAT_R32_TYPELESS                 = 39,
		G_FORMAT_D32_FLOAT                    = 40,
		G_FORMAT_R32_FLOAT                    = 41,
		G_FORMAT_R32_UINT                     = 42,
		G_FORMAT_R32_SINT                     = 43,
		G_FORMAT_R24G8_TYPELESS               = 44,
		G_FORMAT_D24_UNORM_S8_UINT            = 45,
		G_FORMAT_R24_UNORM_X8_TYPELESS        = 46,
		G_FORMAT_X24_TYPELESS_G8_UINT         = 47,
		G_FORMAT_R8G8_TYPELESS                = 48,
		G_FORMAT_R8G8_UNORM                   = 49,
		G_FORMAT_R8G8_UINT                    = 50,
		G_FORMAT_R8G8_SNORM                   = 51,
		G_FORMAT_R8G8_SINT                    = 52,
		G_FORMAT_R16_TYPELESS                 = 53,
		G_FORMAT_R16_FLOAT                    = 54,
		G_FORMAT_D16_UNORM                    = 55,
		G_FORMAT_R16_UNORM                    = 56,
		G_FORMAT_R16_UINT                     = 57,
		G_FORMAT_R16_SNORM                    = 58,
		G_FORMAT_R16_SINT                     = 59,
		G_FORMAT_R8_TYPELESS                  = 60,
		G_FORMAT_R8_UNORM                     = 61,
		G_FORMAT_R8_UINT                      = 62,
		G_FORMAT_R8_SNORM                     = 63,
		G_FORMAT_R8_SINT                      = 64,
		G_FORMAT_A8_UNORM                     = 65,
		G_FORMAT_R1_UNORM                     = 66,
		G_FORMAT_R9G9B9E5_SHAREDEXP           = 67,
		G_FORMAT_R8G8_B8G8_UNORM              = 68,
		G_FORMAT_G8R8_G8B8_UNORM              = 69,
		G_FORMAT_BC1_TYPELESS                 = 70,
		G_FORMAT_BC1_UNORM                    = 71,
		G_FORMAT_BC1_UNORM_SRGB               = 72,
		G_FORMAT_BC2_TYPELESS                 = 73,
		G_FORMAT_BC2_UNORM                    = 74,
		G_FORMAT_BC2_UNORM_SRGB               = 75,
		G_FORMAT_BC3_TYPELESS                 = 76,
		G_FORMAT_BC3_UNORM                    = 77,
		G_FORMAT_BC3_UNORM_SRGB               = 78,
		G_FORMAT_BC4_TYPELESS                 = 79,
		G_FORMAT_BC4_UNORM                    = 80,
		G_FORMAT_BC4_SNORM                    = 81,
		G_FORMAT_BC5_TYPELESS                 = 82,
		G_FORMAT_BC5_UNORM                    = 83,
		G_FORMAT_BC5_SNORM                    = 84,
		G_FORMAT_B5G6R5_UNORM                 = 85,
		G_FORMAT_B5G5R5A1_UNORM               = 86,
		G_FORMAT_B8G8R8A8_UNORM               = 87,
		G_FORMAT_B8G8R8X8_UNORM               = 88,
		G_FORMAT_R10G10B10_XR_BIAS_A2_UNORM   = 89,
		G_FORMAT_B8G8R8A8_TYPELESS            = 90,
		G_FORMAT_B8G8R8A8_UNORM_SRGB          = 91,
		G_FORMAT_B8G8R8X8_TYPELESS            = 92,
		G_FORMAT_B8G8R8X8_UNORM_SRGB          = 93,
		G_FORMAT_BC6H_TYPELESS                = 94,
		G_FORMAT_BC6H_UF16                    = 95,
		G_FORMAT_BC6H_SF16                    = 96,
		G_FORMAT_BC7_TYPELESS                 = 97,
		G_FORMAT_BC7_UNORM                    = 98,
		G_FORMAT_BC7_UNORM_SRGB               = 99,
		G_FORMAT_FORCE_UINT                   = 0xffffffffUL 
	};


	enum TEXTURE_TYPE
	{
		TEX_1D,
		TEX_2D,
		TEX_3D,
		TEX_RENDERTARGET,
		TEX_DEPTHSTENCIL,

		TEX_UNKNOWN,
	};

	enum BUFFER_TYPE
	{
		BT_VERTEX_BUFFER,
		BT_INDEX_BUFFER,
		BT_CONSTANT_BUFFER,
	};

	enum PRIMITIVE_TYPE
	{
		PT_TRIANGLE_LIST,
		PT_TRIANGLE_STRIP,
		PT_LINE_LIST,

	};

	enum MAP_HINT
	{
		MAP_DEFAULT,
		MAP_DISCARD,
		MAP_NO_OVERWRITE,

	};

	enum CPU_ACCESS
	{
		CPU_ACCESS_WRITE   = 0x10000L,
		CPU_ACCESS_READ    = 0x20000L,
	};

	enum G_USAGE 
	{
		G_USAGE_DEFAULT     = 0,
		G_USAGE_IMMUTABLE   = 1,
		G_USAGE_DYNAMIC     = 2,
		G_USAGE_STAGING     = 3 
	};

	enum CLEAR_DS_FLAG
	{
		CLEAR_DEPTH							= 0x01,
		CLEAR_STENCIL						= 0x02,
		CLEAR_ALL							= CLEAR_DEPTH | CLEAR_STENCIL,
	};
	enum LIGHT_TYPE
	{
		LT_POINTLIGHT,
		LT_DIRLIGHT,
		LT_SPOTLIGHT,
		LT_SKYLIGHT,
	};
	struct GraphicsSetting
	{
		std::wstring		sysMod;
		void*				wnd;
		bool				windowed;
		int					frameBufferWidth;
		int					frameBufferHeight;
		G_FORMAT			frameBufferFormat;
		G_FORMAT			depthStencilFormat;
		int					multiSampleCount;
		int					multiSampleQuality;
		int					backBufferCount;

	};

	struct SoundSetting
	{
		std::wstring		sysMod;
		int					maxChannels;
	};
	struct InputSetting
	{
		std::wstring		sysMod;
		void*				wnd;
	};
	struct PhysicsSetting
	{
		std::wstring		sysMod;
	};

	struct SysSetting
	{
		GraphicsSetting		graphics;
		InputSetting		input;
		SoundSetting		sound;
		PhysicsSetting		physics;
	};


	
}
