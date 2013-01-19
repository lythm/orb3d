#include <deferred_shading/dr_gbuffer.hlsl>

float4x4 mvp:MATRIX_WVP;
float4x4 mv:MATRIX_WV;
struct vs_in
{
	float3 pos:POSITION;
	float3 normal:NORMAL;
};
struct vs_out
{
	float4 pos:SV_POSITION;
	float4 s_pos:POSITION;
	float3 normal:NORMAL;
};

vs_out vs_main(vs_in i)
{
	vs_out o;
	o.pos = mul(float4(i.pos, 1), mvp);
	o.normal = mul(float4(i.normal.xyz, 0), mv).xyz;
	o.s_pos = mul(float4(i.pos, 1), mv);
	return o;
}

GBuffer dr_ps_main(vs_out i)
{
	half3 clr = half3(1, 1, 1);
	half specular = 1;
	
	return dr_gbuffer_compose(i.s_pos, normalize(i.normal), clr, specular);
}
RasterizerState rs
{
	CULLMODE						= Back;
};
DepthStencilState dr_ds
{
	DepthEnable						= TRUE;
	DepthFunc						= LESS;
	DepthWriteMask					= ALL;
	StencilEnable					= true;

	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= KEEP;
	FrontFaceStencilPass			= Replace;
	FrontFaceStencilFunc			= ALWAYS;

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass				= KEEP;
	BackFaceStencilFunc				= NEVER;

};
BlendState bs
{
	BLENDENABLE[0]					= false;
	
};
technique11 dr_render_gbuffer
{
	pass p1
	{
		SetDepthStencilState(dr_ds, 1);
		SetRasterizerState(rs);
		SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, dr_ps_main() ) );
	}
}
