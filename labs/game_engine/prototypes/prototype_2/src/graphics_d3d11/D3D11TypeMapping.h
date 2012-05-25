#pragma once


namespace engine
{
	class D3D11TypeMapping
	{
	public:

		static D3D11_USAGE				MapUsage(DEVICE_USAGE usage);
		static UINT						MapCpuAccess(DEVICE_CPU_ACCESS access);
		static DXGI_FORMAT				MapFormat(DEVICE_FORMAT format);
		static D3D11_MAP				MapMap(DEVICE_MAP map);

	private:
		D3D11TypeMapping(void);
		virtual ~D3D11TypeMapping(void);
	};


}