float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;

float3 dir = normalize(float3(1,0, 0));

Texture2D pos_tex;
Texture2D normal_tex;
Texture2D depth_tex;

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

ps_out ps_main(vs_out psin)
{
	ps_out psout;
	
	float4 pos = pos_tex.Sample(diff, psin.uv);
	float4 normal = normal_tex.Sample(diff, psin.uv);

	//float d = pos.z * 20;

	//clamp(d, 0, 1);
	
	float3 d = mul(dir, (float3x3)matView);
	
	d = normalize(d);
	normal = normalize(normal);

	d = float3(0, 0, 1);

	float c = dot(-d, normal.xyz);
	c = max(c, 0);
	psout.color = float4(c, c, c, 1);
	

	normal = ((normal + 1) / 2);
	psout.color = float4(normal.xyz, 1);

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
