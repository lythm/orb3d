#include <dr_utils.hlsl>

Texture2D tex_gbuffer[3]:DR_GBUFFER;

float4x4 wvp:MATRIX_WVP;
float4x4 wv:MATRIX_WV;
float3 v_dir_light = float3( 0, 0, 0);
SamplerState diff
{
    AddressU = clamp;
    AddressV = clamp;
};

float4 Light(half3 normal)
{
	normal = normalize(normal);

	float3 d = -mul(v_dir_light, (float3x3)wv);
	
	d = normalize(d);
	
	float3 ret = dr_light_dir(normal, d);

	return float4(ret, 1);
}

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
PS_INPUT vs_dirlight_main(INPUT i)
{
	PS_INPUT o;
	
	o.pos = float4(i.pos, 1);
	o.uv = i.pos.xy;

	o.uv.x = (o.uv.x + 1.0) / 2.0;
	o.uv.y = (1.0 - o.uv.y) / 2.0;

	return o;
}
PS_OUTPUT ps_dirlight_main(PS_INPUT i)
{
	PS_OUTPUT o;
	
	float2 uv = i.uv;

	half4 normal = tex_gbuffer[1].Sample(diff, uv);
	o.clr = Light(normal.xyz);
	return o;
}

PS_OUTPUT ps_main(PS_INPUT i)
{
	PS_OUTPUT o;

	float2 uv = i.uv;

	half4 normal = tex_gbuffer[1].Sample(diff, uv);
	half4 pos = tex_gbuffer[0].Sample(diff, uv);
	half4 clr = tex_gbuffer[2].Sample(diff, uv);

	o.clr = Light(normal.xyz);
	
	return o;
}
RasterizerState rs
{
	CULLMODE = None;
};
BlendState bs
{
	//ALPHATOCOVERAGEENABLE	= false;
	BLENDENABLE[0]		= true;
	SRCBLEND		= ONE;
	DESTBLEND		= ONE;
	BLENDOP			= ADD;
	SRCBLENDALPHA		= ONE;
	DESTBLENDALPHA		= ONE;
	BLENDOPALPHA		= ADD;
	//RENDERTARGETWRITEMASK[0]= 0xFF;
};
DepthStencilState ds
{
	DepthEnable = FALSE;
	DepthFunc = LESS;
	DepthWriteMask = ZERO;
	StencilEnable = true;
	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= KEEP;
	FrontFaceStencilPass			= KEEP;
	FrontFaceStencilFunc			= EQUAL;

	BackFaceStencilFail			= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass			= KEEP;
	BackFaceStencilFunc			= NEVER;
};
technique11 dir_light
{
	pass p1
	{
		SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(rs);
		SetDepthStencilState(ds, 1);
		SetVertexShader( CompileShader( vs_4_0, vs_dirlight_main() ) );
		SetPixelShader( CompileShader( ps_4_0, ps_dirlight_main()));
	}
}

/*technique11 point_light
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

*/