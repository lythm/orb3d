#include <dr_utils.hlsl>


float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;
float3 dir = normalize(float3(0, -1, 1));

float2 vp:VP_SIZE;

Texture2D tex_gbuffer[3]:DR_GBUFFER;
Texture2D tex_abuffer:DR_ABUFFER;


SamplerState diff
{
	AddressU = clamp;
	AddressV = clamp;

	filter = MIN_MAG_MIP_POINT ;
	BorderColor = float4(0,0,0,0);
	MinLod = 0;
	MaxLod = 0;
};

struct vs_in
{
	float3 pos:POSITION;
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

	float2 uv = vsout.pos.xy;

	uv.x = (uv.x + 1.0) / 2.0;
	uv.y = (1.0 - uv.y) / 2.0;

	vsout.uv = uv;
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

	float2 uv = psin.uv;

	
		

	half4 normal = tex_gbuffer[1].Sample(diff, uv);
	half4 pos = tex_gbuffer[0].Sample(diff, uv);
	half4 clr = tex_gbuffer[2].Sample(diff, uv);

	float depth = pos.z;

	//psout.color = NormalColor(normal.xyz);
	//psout.color = Light(normal.xyz, clr);
	
	//psout.color = DepthColor(depth);
	//psout.color = float4(clr.xyz, 1);

	return psout;
}
ps_out ps_main_1(vs_out psin)
{
	ps_out psout;

	//float2 uv = psin.uv;
	
	float2 uv = psin.pos.xy;
	uv = uv / psin.pos.w;
	
	uv.x = (uv.x ) / vp.x;
	
	uv.y = (uv.y ) / vp.y;
	
	//uv = uv * 0.5 + 0.5;
	

	float4 clr = tex_gbuffer[2].Sample(diff, uv);
	clr.w = 1;
	psout.color = tex_abuffer.Sample(diff,uv);
	psout.color = psout.color;// * clr;


	//psout.color = float4(uv.x , uv.y,0,1);

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
BlendState bs
{
	//ALPHATOCOVERAGEENABLE	= false;
	BLENDENABLE[0]		= false;
	SRCBLEND		= DEST_COLOR;
	DESTBLEND		= ZERO;
	BLENDOP			= ADD;
	SRCBLENDALPHA		= ONE;
	DESTBLENDALPHA		= ONE;
	BLENDOPALPHA		= ADD;
	//RENDERTARGETWRITEMASK[0]= 0xFF;
};
technique11 test
{
  pass p1
  {
	SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 1);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main_1(  ) ) );

  }
}
