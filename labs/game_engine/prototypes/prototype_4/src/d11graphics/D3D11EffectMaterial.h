#pragma once

#include "core\Material.h"

#include "core\VertexFormat.h"

namespace engine
{
	class D3D11EffectMaterial : public Material
	{
	public:
		D3D11EffectMaterial(ID3D11DeviceContext* pContext);
		virtual ~D3D11EffectMaterial(void);

		void								ApplyVertexFormat();

		bool								BeginPass(int& nPass);
		void								ApplyPass(int index);
		void								EndPass();
		
		int									FindPass(const std::string& name);
		void								Release();

		bool								LoadFromFile(const char* szFile);

		// parameter by name
		void								SetMatrixByName(const char* szParam, const math::Matrix44& mat);
		void								SetTextureByName(const char* szName, TexturePtr pTex);
		void								SetVectorByName(const char* szName, const math::Vector3& v);
		void								SetVectorByName(const char* szName, const math::Vector4& v);
		void								SetVectorByName(const char* szName, const math::Vector2& v);
		void								SetFloatByName(const char* szName, float v);
		void								SetIntByName(const char* szName, int v);

		// parameter by semantic
		void								SetMatrixBySemantic(const char* szSemantic, const math::Matrix44& mat);
		void								SetTextureBySemantic(const char* szName, TexturePtr pTex);
		void								SetVectorBySemantic(const char* szName, const math::Vector3& v);
		void								SetVectorBySemantic(const char* szName, const math::Vector4& v);
		void								SetVectorBySemantic(const char* szName, const math::Vector2& v);
		void								SetFloatBySemantic(const char* szName, float v);
		void								SetIntBySemantic(const char* szName, int v);

		bool								SetVertexFormat(const VertexFormat& format);

	private:
		
		ID3D11InputLayout*					m_pIL;
		ID3D11DeviceContext*				m_pContext;

		ID3DX11Effect*						m_pEffect;

		ID3D11Device*						m_pDevice;

		ID3DX11EffectTechnique*				m_pTech;

		int									m_nPass;

	};
}
