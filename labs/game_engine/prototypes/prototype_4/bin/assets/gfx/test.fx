float4x4 mat:WORLDVIEWPROJ;

//float3 dir = normalize(float3(1,-1, 1));

Texture2D diff_tex;
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
	vsout.pos = mul(float4(vsin.pos, 1), mat);

	vsout.uv = vsin.uv;

	return vsout;
}

struct ps_out
{
	float4 color:SV_TARGET;
};

ps_out ps_main(vs_out psin)
{
	ps_out psout;
	
	psout.color = diff_tex.Sample(diff, psin.uv) * float4(0.5, 1, 1, 1);

	//psout.color = float4(1,1,1,1);
	return psout;
}

RasterizerState rs
{
	CULLMODE = None;
};
technique11 test
{
  pass p1
  {
	SetRasterizerState(rs);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );

  }
}
