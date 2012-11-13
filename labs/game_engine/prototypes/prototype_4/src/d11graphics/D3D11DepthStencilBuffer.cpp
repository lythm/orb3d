#include "d11graphics_pch.h"
#include "D3D11DepthStencilBuffer.h"
#include "D3D11Texture.h"
#include "D3D11Format.h"


namespace engine
{
	D3D11DepthStencilBuffer::D3D11DepthStencilBuffer(ID3D11DeviceContext* pContext)
	{

		m_pContext					= pContext;

		m_pDevice					= NULL;

		m_pContext->GetDevice(&m_pDevice);
		m_pDepthStencilView			= NULL;

	}


	D3D11DepthStencilBuffer::~D3D11DepthStencilBuffer(void)
	{
	}

	bool D3D11DepthStencilBuffer::Create(int w, int h, G_FORMAT format, bool asTexture)
	{

		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));

		td.ArraySize = 1;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		asTexture ? td.BindFlags |= D3D11_BIND_SHADER_RESOURCE : td.BindFlags;

		m_bAsTexture = asTexture;

		td.CPUAccessFlags = 0;
		td.Format = D3D11Format::Convert(format);
		td.Height = h;
		td.MipLevels = 1;
		td.MiscFlags = 0;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.Width = w;

		
		if(FAILED(m_pDevice->CreateTexture2D(&td, NULL, &m_pBuffer)))
		{
			return DepthStencilBufferPtr();
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC d;
		ZeroMemory(&d, sizeof(d));

		d.Format = DXGI_FORMAT_D16_UNORM;//D3D11Format::Convert(format);
		d.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		d.Flags = 0;
		d.Texture2D.MipSlice = 0;

		if(FAILED(m_pDevice->CreateDepthStencilView( m_pBuffer, &d, &m_pDepthStencilView)))
		{
			return false;
		}

		return true;
	}
	void D3D11DepthStencilBuffer::Release()
	{
		if(m_pTex)
		{
			m_pTex->Release();
			m_pTex.reset();
		}
		if(m_pBuffer)
		{
			m_pBuffer->Release();
			m_pBuffer = NULL;
		}

		if(m_pDepthStencilView)
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = NULL;
		}

		m_pDevice->Release();
		m_pContext = NULL;
	}
	
	ID3D11DepthStencilView*	D3D11DepthStencilBuffer::GetD3D11DepthStencilView()
	{
		return m_pDepthStencilView;
	}
	TexturePtr D3D11DepthStencilBuffer::AsTexture(G_FORMAT format)
	{
		if(m_bAsTexture == false)
		{
			return TexturePtr();
		}

		if(m_pTex == TexturePtr())
		{
			m_pTex = CreateTexture(format);
			return m_pTex;
		}

		ID3D11ShaderResourceView* pView = ((D3D11Texture*)m_pTex.get())->GetShaderResourceView();
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		pView->GetDesc(&desc);

		if(desc.Format == D3D11Format::Convert(format))
		{
			return m_pTex;
		}
		
		m_pTex->Release();

		m_pTex = CreateTexture(format);
		return m_pTex;

	}
	TexturePtr D3D11DepthStencilBuffer::CreateTexture(G_FORMAT format)
	{
		D3D11Texture* pTex = new D3D11Texture(m_pContext);
		if(pTex->CreateFromRes(m_pBuffer, format) == false)
		{
			delete pTex;
			return TexturePtr();
		}
		m_pBuffer->AddRef();

		m_pTex = TexturePtr(pTex);
		return m_pTex;
	}
	void D3D11DepthStencilBuffer::Clear(float depth, int stencil)
	{
		m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , depth, stencil);
	}

}
