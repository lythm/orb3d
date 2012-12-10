#include <dr_utils.hlsl>

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
	float3 eyepos:POSITION1;
	float3 normal:NORMAL;
};

vs_out vs_main(vs_in vsin)
{
	vs_out vsout;
	vsout.pos = mul(float4(vsin.pos, 1), mvp);
	vsout.eyepos = mul(float4(vsin.pos, 1), mv);
	vsout.normal = mul(float4(vsin.normal.xyz, 0), mv).xyz;

	return vsout;
}

GBuffer dr_ps_main(vs_out psin)
{
	
	half3 clr = half3(0.5, 0.6, 0.9);
	half specular = 1;

	GBuffer g;
	g.pos = half4(psin.pos.xyz, 1);
	g.normal = half4(psin.normal, 1);
	g.diff = half4(clr.xyz, specular);

	return g;
}
RasterizerState rs
{
	CULLMODE = Back;
};
DepthStencilState dr_ds
{
	DepthEnable = TRUE;
	DepthFunc = LESS;
	DepthWriteMask = ALL;
	StencilEnable = false;

};

technique11 dr_render_gbuffer
{
	pass p1
	{
		SetDepthStencilState(dr_ds, 0);
		SetRasterizerState(rs);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, dr_ps_main() ) );
	}
}
