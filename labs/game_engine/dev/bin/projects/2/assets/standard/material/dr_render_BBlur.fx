#include <deferred_shading/dr_gbuffer.hlsl>

Texture2D<float4> tex_ao;
Texture2D<float4> tex_input;
Texture2D<half4> tex_gbuffer[3]:DR_GBUFFER;

float2 g_input_size;

SamplerState Sampler_GBlur
{
	AddressU = wrap;
	AddressV = wrap;

	filter = MIN_POINT_MAG_MIP_LINEAR ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};


static const int g_cKernelSize = 13;

float2 PixelKernel[g_cKernelSize] =
{
    { 0, -6 },
    { 0, -5 },
    { 0, -4 },
    { 0, -3 },
    { 0, -2 },
    { 0, -1 },
    { 0,  0 },
    { 0,  1 },
    { 0,  2 },
    { 0,  3 },
    { 0,  4 },
    { 0,  5 },
    { 0,  6 },
};


static const float BlurWeights[g_cKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};




//-----------------------------------------------------------------------------
// Pixel Shader: HorizontalBlur
// Desc: Blurs the image vertically
//-----------------------------------------------------------------------------
float4 BBlur_V(Texture2D<float4> tex_clr, float2 uv)
{
    float4 Color = 0;
	
	float dp = dr_gbuffer_get_position(tex_gbuffer, uv).z;

    for (int i = 0; i < g_cKernelSize; i++)
    {   
		float2 offset = PixelKernel[i].xy / g_input_size;
		float ds = dr_gbuffer_get_position(tex_gbuffer, uv + offset).z;

		Color += tex_clr.Sample( Sampler_GBlur, uv + offset ) * BlurWeights[i] * (1 / (1 + abs(dp - ds) * 0.1));
    }

    return Color;
}

float4 BBlur_H(Texture2D<float4> tex_clr, float2 uv)
{
    float4 Color = 0;
	
	float dp = dr_gbuffer_get_position(tex_gbuffer, uv).z;

	for (int i = 0; i < g_cKernelSize; i++)
    {   
		float2 offset = PixelKernel[i].yx / g_input_size;
		float ds = dr_gbuffer_get_position(tex_gbuffer, uv + offset).z;
		Color += tex_clr.Sample( Sampler_GBlur, uv + offset ) * BlurWeights[i] * (1 / (1 + abs(dp - ds) * 0.1));
    }
	
    return Color;
}


struct vs_in
{
	float3 pos:POSITION;
};
struct vs_out
{
	float4 pos:SV_POSITION;
	float4 s_pos:POSITION;
};

vs_out vs_main(vs_in i)
{
	vs_out o;
	o.pos = float4(i.pos.xyz, 1);
	o.s_pos = o.pos;
	return o;
}

struct ps_out
{
	float4 color:SV_TARGET;
};

ps_out ps_main(vs_out i)
{
	ps_out o;

	float2 uv = dr_gbuffer_screenpos_2_uv(i.s_pos);
	float4 c = tex_input.Sample(Sampler_GBuffer,uv);

	float ao = BBlur_H(tex_ao, uv);
	ao += BBlur_V(tex_ao, uv);
	ao /= 2;

	o.color = c - ao;

	o.color.w = 1;

	//o.color = float4(1, 1, 1, 1);
	return o;
}
RasterizerState rs
{
	CULLMODE				= None;
};
DepthStencilState ds
{
	DepthEnable				= FALSE;
	DepthFunc				= LESS;
	DepthWriteMask				= ZERO;
	StencilEnable				= false;
	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= KEEP;
	FrontFaceStencilPass			= KEEP;
	FrontFaceStencilFunc			= EQUAL;

	BackFaceStencilFail			= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass			= KEEP;
	BackFaceStencilFunc			= NEVER;
};
BlendState bs
{
	BLENDENABLE[0]				= false;
	
};
technique11 T_GBlur_H
{
  pass p1
  {
	SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 1);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main() ) );

  }
}
technique11 T_GBlur_V
{
	pass p1
  {
	SetBlendState( bs, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 1);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main() ) );

  }
};