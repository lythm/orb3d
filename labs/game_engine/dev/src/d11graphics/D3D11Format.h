#pragma once


namespace ld3d
{
	class D3D11Format
	{
	public:
		D3D11Format(void);
		virtual ~D3D11Format(void);


		static DXGI_FORMAT						Convert(G_FORMAT format);
		static D3D11_CPU_ACCESS_FLAG			Convert(CPU_ACCESS acc);
		static D3D_PRIMITIVE_TOPOLOGY			Convert(PRIMITIVE_TYPE p);
	};


}