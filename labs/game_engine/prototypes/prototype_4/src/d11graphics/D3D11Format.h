#pragma once


namespace engine
{
	class D3D11Format
	{
	public:
		D3D11Format(void);
		virtual ~D3D11Format(void);


		static DXGI_FORMAT						Convert(G_FORMAT format);
	};


}