#include <deferred_shading/dr_gbuffer.hlsl>
#include <deferred_shading/dr_light.hlsl>

Texture2D<half4> tex_gbuffer[3]:DR_GBUFFER;
float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;

PointLight	light;

struct INPUT
{
	float3 pos:POSITION;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD;
};
struct PS_OUTPUT
{
	float4 clr:SV_TARGET;
};
PS_INPUT vs_main(INPUT i)
{
	PS_INPUT o;
	
	o.pos = float4(i.pos, 1);
	o.uv = i.pos.xy;

	o.uv.x = (o.uv.x + 1.0) / 2.0;
	o.uv.y = (1.0 - o.uv.y) / 2.0;

	return o;
}
PS_OUTPUT ps_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	half3 n = dr_gbuffer_get_normal(tex_gbuffer, i.uv);
	half4 p = dr_gbuffer_get_position(tex_gbuffer, i.uv);

	o.clr.xyz = dr_light_point(p, n, light, wv);
	o.clr.w = 1;

	return o;
}

technique11 dir_light
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

