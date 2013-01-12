#include <deferred_shading/dr_gbuffer.hlsl>
#include <deferred_shading/dr_light.hlsl>

Texture2D<half4> tex_gbuffer[3]:DR_GBUFFER;
float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;
float4x4 i_p:MATRIX_I_PROJ;
PointLight	light;

struct INPUT
{
	float3 pos:POSITION;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float4 s_pos:POSITION;
};
struct PS_OUTPUT
{
	float4 clr:SV_TARGET;
};
PS_INPUT vs_main(INPUT i)
{
	PS_INPUT o;
	
	o.pos = mul(float4(i.pos, 1), wvp);
	o.s_pos = o.pos;
	return o;
}
PS_OUTPUT ps_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	float2 uv = dr_gbuffer_screenpos_2_uv(i.s_pos);

	half3 n = dr_gbuffer_get_normal(tex_gbuffer, uv);
	half4 p = dr_gbuffer_get_position(tex_gbuffer, uv);

	float3 v_pos =p;// mul(p, i_p).xyz;
	o.clr.xyz = dr_light_point(v_pos, n, light, wv);
	o.clr.w = 1;

	return o;
}

technique11 point_light
{
	pass p1
	{
		SetBlendState( BS_Light, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(RS_Light);
		SetDepthStencilState(DS_Light, 1);
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_main()));
	}
}

