#include <deferred_shading/dr_gbuffer.hlsl>

Texture2D<float4> post_output;


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

	o.color = float4(post_output.Sample(Sampler_GBuffer, uv).xyz, 1);

	//o.color = float4(1, 1, 1, 1);
	return o;
}
RasterizerState rs
{
	CULLMODE						= Back;
};
DepthStencilState ds
{
	DepthEnable						= FALSE;
	DepthFunc						= LESS;
	DepthWriteMask					= ZERO;
	StencilEnable					= true;
	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= KEEP;
	FrontFaceStencilPass			= KEEP;
	FrontFaceStencilFunc			= ALWAYS;

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail		= KEEP;
	BackFaceStencilPass				= KEEP;
	BackFaceStencilFunc				= NEVER;
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
