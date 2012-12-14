#include <dr_utils.hlsl>


float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;
float3 dir = normalize(float3(0, -1, 1));


Texture2D tex_gbuffer[3]:DR_GBUFFER;

Texture2D tex_pos;
Texture2D tex_normal;
Texture2D tex_diff;

SamplerState diff
{
    AddressU = clamp;
    AddressV = clamp;
};

struct vs_in
{
	float3 pos:POSITION;
	float2 uv:TEXCOORD;	
};
struct vs_out
{
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD;
};

vs_out vs_main(vs_in vsin)
{
	vs_out vsout;
	vsout.pos = float4(vsin.pos.xyz, 1);

	vsout.uv = vsin.uv;

	return vsout;
}

struct ps_out
{
	float4 color:SV_TARGET;
};

float4 DepthColor(float depth)
{
	depth = depth * 15;
	clamp(depth, 0, 1);
	
	//depth = 1 - depth;

	return float4(depth, depth, depth, 1);
}
float4 NormalColor(float3 normal)
{
	normal = ((normal + 1) / 2);
	normal = normalize(normal);
	return float4(normal.xyz, 1);
}

float4 Light(half3 normal, float3 clr)
{
	normal = normalize(normal);

	float3 d = -mul(dir, (float3x3)matView);
	
	d = normalize(d);
	
	float3 ret = dr_light_dir(normal, d);

	clr = clr * ret;
	return float4(clr, 1);
}
ps_out ps_main(vs_out psin)
{
	ps_out psout;
	half4 normal = tex_gbuffer[1].Sample(diff, psin.uv);
	half4 pos = tex_gbuffer[0].Sample(diff, psin.uv);
	half4 clr = tex_gbuffer[2].Sample(diff, psin.uv);

	float depth = pos.z;

	//psout.color = NormalColor(normal.xyz);
	psout.color = Light(normal.xyz, clr);
	
	//psout.color = DepthColor(depth);
	//psout.color = float4(clr.xyz, 1);

	return psout;
}

RasterizerState rs
{
	CULLMODE = None;
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

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass				= KEEP;
	BackFaceStencilFunc				= NEVER;
};

technique11 test
{
  pass p1
  {
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 1);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );

  }
}
