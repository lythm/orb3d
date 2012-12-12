#include <dr_utils.hlsl>

Texture2D tex_gbuffer[3]:DR_GBUFFER;
Texture2D tex_abuffer:DR_ABUFFER;

float4x4 wvp:MATRIX_WVP;

struct INPUT
{
	float3 pos:POSITION;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
};
struct PS_OUTPUT
{
	float4 clr:SV_TARGET;
};
PS_INPUT vs_main(INPUT i)
{
	PS_INPUT o;
	
	o.pos = mul(float4(i.pos, 1), wvp);

	return o;
}
PS_OUTPUT ps_dirlight_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	o.clr = float4(0, 0, 0, 0);
	return o;
}

PS_OUTPUT ps_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	o.clr = float4(0, 0, 0, 0);
	return o;
}

technique11 dir_light
{
	pass p1
	{
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_dirlight_main()));
	}
}
technique11 point_light
{
	pass p1
	{
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );
	}
}
technique11 spot_light
{
	pass p1
	{
		SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );
	}
}
