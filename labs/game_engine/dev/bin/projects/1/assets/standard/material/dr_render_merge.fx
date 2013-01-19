#include <deferred_shading/dr_gbuffer.hlsl>

float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;

Texture2D<half4> tex_gbuffer[3]:DR_GBUFFER;
Texture2D<float4> tex_abuffer:DR_ABUFFER;


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
	float4 l = tex_abuffer.Sample(Sampler_GBuffer,uv);

	o.color.xyz = l.xyz * d;
	o.color.w = 1;
	return o;
}
RasterizerState rs
{
	CULLMODE				= Back;
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
	FrontFaceStencilFunc			= EQUAL;

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
