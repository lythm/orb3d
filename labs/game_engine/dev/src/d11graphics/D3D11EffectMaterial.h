#pragma once

#include "core\Material.h"

#include "core\VertexFormat.h"

namespace ld3d
{
	class D3D11EffectMaterial : public Material
	{
		struct EffectSemntics
		{
			ID3DX11EffectMatrixVariable*		m_pWorldTM;
			ID3DX11EffectMatrixVariable*		m_pViewTM;
			ID3DX11EffectMatrixVariable*		m_pProjTM;
			ID3DX11EffectMatrixVariable*		m_pInvWorldTM;
			ID3DX11EffectMatrixVariable*		m_pInvViewTM;
			ID3DX11EffectMatrixVariable*		m_pInvProjTM;

			ID3DX11EffectMatrixVariable*		m_pWVTM;
			ID3DX11EffectMatrixVariable*		m_pWVPTM;

			ID3DX11EffectMatrixVariable*		m_pInvWVTM;
			ID3DX11EffectMatrixVariable*		m_pInvWVPTM;
			ID3DX11EffectMatrixVariable*		m_pInvVPTM;

			ID3DX11EffectShaderResourceVariable* m_pGBuffer;
			ID3DX11EffectShaderResourceVariable* m_pABuffer;
		};
	public:
		D3D11EffectMaterial(ID3D11DeviceContext* pContext);
		virtual ~D3D11EffectMaterial(void);

		void								ApplyVertexFormat();

		bool								Begin(int& nPass);
		void								ApplyPass(int index);
		void								End();
		
		int									FindPass(const std::string& name);
		void								Release();

		bool								LoadFromFile(const char* szFile);


		void								SetViewMatrix(const math::Matrix44& val);
		void								SetProjMatrix(const math::Matrix44& val);
		void								SetWorldMatrix(const math::Matrix44& val);

		// parameter by name
		void								SetMatrixByName(const char* szParam, const math::Matrix44& mat);
		void								SetTextureByName(const char* szName, TexturePtr pTex);
		void								SetVectorByName(const char* szName, const math::Vector3& v);
		void								SetVectorByName(const char* szName, const math::Vector4& v);
		void								SetVectorByName(const char* szName, const math::Vector2& v);
		void								SetFloatByName(const char* szName, float v);
		void								SetIntByName(const char* szName, int v);
		void								SetCBByName(const char* szName, void* buffer, int size);
		// parameter by semantic
		void								SetMatrixBySemantic(const char* szSemantic, const math::Matrix44& mat);
		void								SetTextureBySemantic(const char* szName, TexturePtr pTex);
		void								SetVectorBySemantic(const char* szName, const math::Vector3& v);
		void								SetVectorBySemantic(const char* szName, const math::Vector4& v);
		void								SetVectorBySemantic(const char* szName, const math::Vector2& v);
		void								SetFloatBySemantic(const char* szName, float v);
		void								SetIntBySemantic(const char* szName, int v);
		void								SetCBBySemantic(const char* szName, GPUBufferPtr pCB);

		bool								SetVertexFormat(const VertexFormat& format);

		bool								SelectTechByName(const char* szName);

		void								SetABuffer(RenderTargetPtr pABuffer);
		void								SetGBuffer(RenderTargetPtr pGBuffer);
	private:
		void								UpdateSemantics();
		void								OutputDebugInfo(ID3D10Blob* pBlob);
	private:
		
		ID3D11InputLayout*					m_pIL;
		ID3D11DeviceContext*				m_pContext;

		ID3DX11Effect*						m_pEffect;

		ID3D11Device*						m_pDevice;

		ID3DX11EffectTechnique*				m_pTech;

		int									m_nPass;

		math::Matrix44						m_worldTM;
		math::Matrix44						m_viewTM;
		math::Matrix44						m_projTM;

		EffectSemntics						m_semantics;

	};
}
