#include <deferred_shading/dr_gbuffer.hlsl>

float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;

Texture2D<half4>	tex_gbuffer[3]:DR_GBUFFER;
Texture2D<float4>	tex_input;
Texture2D<float4>	tex_ssao_rand:SSAO_RAND;		

float g_random_size	= 64;
float g_sample_rad	= 1;
float g_intensity	= 1;
float g_scale		= 1;
float g_bias		= 0.2;
float2 g_screen_size = float2(640,640);


SamplerState Sampler_SSAORand
{
	AddressU = wrap;
	AddressV = wrap;

	filter = MIN_MAG_MIP_LINEAR ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};

float2 getRandom(in float2 uv)
{
	return normalize(tex_ssao_rand.Sample(Sampler_SSAORand, g_screen_size * uv / g_random_size).xy * 2.0f - 1.0f);
}
float doAmbientOcclusion(in float2 tcoord,in float2 uv, in float3 p, in float3 cnorm)
{
	float3 diff			= dr_gbuffer_get_position(tex_gbuffer, tcoord + uv) - p;
	
	const float3 v		= normalize(diff);
	const float d		= length(diff)*g_scale;
	
	float a = 0;
	int i = 0;
	//for(float c = 0.1; c < d; c+= 1)
	//{
	//	a += max(0.0,dot(cnorm,v)-g_bias)*(sqrt(1.0/(1.0+c*c)))*g_intensity;
	//	i += 1;
	//}

	//a /= i;

	a += max(0.0,dot(cnorm,v)-g_bias)*(sqrt(1.0/((1.0+d)*(1 + d))))*g_intensity;
	return a;

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


	float3 d = dr_gbuffer_get_diffuse(tex_gbuffer, uv);
	float3 p = dr_gbuffer_get_position(tex_gbuffer, uv);
	float3 n = dr_gbuffer_get_normal(tex_gbuffer, uv);
	
	


// ====================================SSAO===================================


	o.color.rgb = 1.0f;
	const float2 vec[4] = {float2(1,0),float2(-1,0),
			float2(0,1),float2(0,-1)};
 
	float2 rand = getRandom(uv);

	//float2 rand = tex_ssao_rand.Sample(Sampler_GBuffer, uv).xy;
 
	float ao = 0.0f;
	float rad = g_sample_rad/p.z;
 
//**SSAO Calculation**//
	int iterations = 4;
	for (int j = 0; j < iterations; ++j)
	{
		float2 coord1 = reflect(vec[j],rand)*rad;
		float2 coord2 = float2(coord1.x*0.707 - coord1.y*0.707,
			  coord1.x*0.707 + coord1.y*0.707);
  
		ao += doAmbientOcclusion(uv,coord1*0.25, p, n);
		ao += doAmbientOcclusion(uv,coord2*0.5, p, n);
		ao += doAmbientOcclusion(uv,coord1*0.75, p, n);
		ao += doAmbientOcclusion(uv,coord2, p, n);
	}
	ao/=(float)iterations*4.0;

//============================================================================
	
	//float4 l = tex_input.Sample(Sampler_GBuffer,uv);

	o.color.xyz = ao;
	o.color.w = 1;

//	o.color.xyz = 1 - ao;
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
technique11 test
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
