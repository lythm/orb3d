#include "graphics_pch.h"
#include "D3D11TypeMapping.h"


namespace engine
{
	D3D11TypeMapping::D3D11TypeMapping(void)
	{
	}


	D3D11TypeMapping::~D3D11TypeMapping(void)
	{
	}


	DXGI_FORMAT D3D11TypeMapping::MapFormat(DEVICE_FORMAT format)
	{
		return (DXGI_FORMAT)format;
	}
	D3D11_USAGE D3D11TypeMapping::MapUsage(DEVICE_USAGE usage)
	{
		D3D11_USAGE d3d11_usage = D3D11_USAGE_DEFAULT;

		switch(usage)
		{
		case USAGE_STATIC:
			d3d11_usage = D3D11_USAGE_DEFAULT;
			break;
		case USAGE_DYNAMIC:
			d3d11_usage = D3D11_USAGE_DYNAMIC;
			break;
		default:
			assert(0);
			break;
		}

		return d3d11_usage;
	}

	UINT D3D11TypeMapping::MapCpuAccess(DEVICE_CPU_ACCESS access)
	{
		UINT d3d11_access = 0;

		switch(access)
		{
		case CPU_ACCESS_READ:
			d3d11_access = D3D11_CPU_ACCESS_READ;
			break;
		case CPU_ACCESS_WRITE:
			d3d11_access = D3D11_CPU_ACCESS_WRITE;
			break;
		default:
			assert(0);
			break;
		}
		return d3d11_access;

	}

	D3D11_MAP D3D11TypeMapping::MapMap(DEVICE_MAP map)
	{
		return (D3D11_MAP)map;
	}
}