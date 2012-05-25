#include "graphics_pch.h"
#include "D3D11GraphicsFX.h"
#include <D3Dcompiler.h>


namespace engine
{
	D3D11GraphicsFX::D3D11GraphicsFX(ID3D11DeviceContext* pContext)
	{
		m_pContext = pContext;

		
		Pass pass;
		pass.m_pPixelShader = NULL;
		pass.m_pVertexShader = NULL;
		pass.m_pVertexShaderConstantBuffer = NULL;

		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		ID3DBlob* pErrorBlob;
		ID3DBlob* pBlobOut;

		hr = D3DX11CompileFromFile( L"./assets/gfx/shaders/test.vs", NULL, NULL, "VS", "vs_4_0", dwShaderFlags, 0, NULL, &pBlobOut, &pErrorBlob, NULL );

//		char* pp = (char*)pErrorBlob->GetBufferPointer();
		//pErrorBlob->Release();
		//	pErrorBlob = NULL;

		ID3D11Device* pDevice = NULL;

		m_pContext->GetDevice(&pDevice);

		hr = pDevice->CreateVertexShader(pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), NULL, &pass.m_pVertexShader);



		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },  
		};
		UINT numElements = ARRAYSIZE(layout);

		pDevice->CreateInputLayout( layout, numElements, pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), &m_pInputLayout);

		pBlobOut->Release();


		hr = D3DX11CompileFromFile( L"./assets/gfx/shaders/test.ps", NULL, NULL, "PS", "ps_4_0", dwShaderFlags, 0, NULL, &pBlobOut, &pErrorBlob, NULL );

		//pErrorBlob->Release();
		//pErrorBlob = NULL;

		pDevice->CreatePixelShader(pBlobOut->GetBufferPointer(), pBlobOut->GetBufferSize(), NULL, &pass.m_pPixelShader);
		pBlobOut->Release();


		struct TMP
		{
			math::Matrix44 world;
			math::Matrix44 view;
			math::Matrix44 proj;
		};


		

		D3D11_BUFFER_DESC desc;

		desc.BindFlags =  D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TMP);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = D3D11_USAGE_DYNAMIC;

		

		//HRESULT ret = pDevice->CreateBuffer(&desc, NULL, &pass.m_pVertexShaderConstantBuffer);
		
		D3D11_MAPPED_SUBRESOURCE map_desc;

		D3D11_MAP map = D3D11_MAP_WRITE_DISCARD;

		//ret = m_pContext->Map(pass.m_pVertexShaderConstantBuffer, 0, map, 0, &map_desc);
		//
		//TMP t;

		//t.world.SetIdentity();
		////t.view.SetIdentity();
		//t.proj.SetIdentity();

		//t.view = math::MatrixLookAtLH(math::Vector3(0, 0, -0.5), math::Vector3(0, 0, 0), math::Vector3(0, 1,0));

		//t.proj = math::MatrixPerspectiveFovLH(3.14 / 2, 4.0/ 3.0, 0.1 , 100.0f);

		//memcpy(map_desc.pData, &t, sizeof(TMP));

		//m_pContext->Unmap(pass.m_pVertexShaderConstantBuffer, 0);

		pDevice->Release();

		m_PassArray.push_back(pass);

	}


	D3D11GraphicsFX::~D3D11GraphicsFX(void)
	{

	}
	void D3D11GraphicsFX::Release()
	{
		for(size_t i = 0; i < m_PassArray.size();++i)
		{
			Pass& pass = m_PassArray[i];

			pass.m_pPixelShader->Release();
			pass.m_pVertexShader->Release();
		}
		m_PassArray.clear();

		
		
		if(m_pInputLayout != NULL)
		{
			m_pInputLayout->Release();
			m_pInputLayout = NULL;
		}
	
		m_pContext		= NULL;

	}
	

	ID3D11InputLayout* D3D11GraphicsFX::GetInputLayout()
	{
		return m_pInputLayout;
	}
	
	bool D3D11GraphicsFX::Begin(uint32& passCount)
	{
		m_pContext->IASetInputLayout(m_pInputLayout);

		passCount = (uint32)m_PassArray.size();
		return true;
	}
	void D3D11GraphicsFX::ApplyPass(uint32 iPass)
	{
		Pass& p = m_PassArray[iPass];


		//m_pContext->VSSetConstantBuffers(0, 1, &p.m_pVertexShaderConstantBuffer);

		m_pContext->VSSetShader(p.m_pVertexShader, NULL, 0);
		m_pContext->PSSetShader(p.m_pPixelShader, NULL, 0);
	}
	void D3D11GraphicsFX::End()
	{

	}
}
