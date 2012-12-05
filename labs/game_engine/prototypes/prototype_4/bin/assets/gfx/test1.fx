float4x4 mat:MATRIX_WVP;
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
	float4 pos:SV_TARGET0;
	float4 normal:SV_TARGET1;
	float  depth:SV_TARGET2;
};

ps_out ps_main(vs_out psin)
{
	ps_out psout;
	
	psout.depth = psin.pos.z / psin.pos.w;
	
	return psout;
}

RasterizerState rs
{
	CULLMODE = Back;
};

DepthStencilState ds
{
	DepthEnable = TRUE;
	DepthFunc = LESS;
	DepthWriteMask = ALL;
	StencilEnable = false;

};
technique11 test
{
  pass p1
  {
	SetRasterizerState(rs);
	SetDepthStencilState(ds, 0);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );

  }
}
