float4x4 mat:MATRIX_WVP;
float4x4 matView:MATRIX_WV;

float3 dir = normalize(float3(0, -1, 1));

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

float4 Light(vs_out psin)
{
	ps_out psout;
	
	float4 normal = normal_tex.Sample(diff, psin.uv);
	normal = normalize(normal);

	float3 d = -mul(dir, (float3x3)matView);
	
	d = normalize(d);
	
	float c = dot(d, normal.xyz);
	c = max(c, 0);
	
	return float4(c, c, c, 1);
}
ps_out ps_main(vs_out psin)
{
	ps_out psout;
	float4 normal = normal_tex.Sample(diff, psin.uv);
	float4 pos = pos_tex.Sample(diff, psin.uv);
	float depth = depth_tex.Sample(diff, psin.uv);

	//psout.color = NormalColor(normal.xyz);
	//psout.color = Light(psin);
	psout.color = DepthColor(depth);

	return psout;
}

RasterizerState rs
{
	CULLMODE = None;
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
