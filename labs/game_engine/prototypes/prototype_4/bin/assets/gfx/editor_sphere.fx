float4x4 mat:MATRIX_WVP;

struct vs_in
{
	float3 pos:POSITION;
	float3 normal:NORMAL;
};
struct vs_out
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
};

vs_out vs_main(vs_in vsin)
{
	vs_out vsout;
	vsout.pos = mul(float4(vsin.pos, 1), mat);

	return vsout;
}

struct ps_out
{
	float4 color:SV_TARGET;
};

ps_out ps_main(vs_out psin) 
{
	ps_out psout;
	
	
	psout.color = float4(1,1,1,1);
	
	return psout;
}
float ps_depth(vs_out psin) : SV_DEPTH
{
	return psin.pos.z;
}
RasterizerState rs
{
	CULLMODE = None;
};
DepthStencilState ds1
{
	DepthEnable = TRUE;
	DepthFunc = LESS_EQUAL;
	DepthWriteMask = ZERO;
	StencilEnable = false;

};
DepthStencilState ds2
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
	SetDepthStencilState(ds1, 0);
	SetRasterizerState(rs);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main() ) );
  }

  pass DEPTH_PASS
  {
	SetDepthStencilState(ds2, 0);
	SetRasterizerState(rs);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_depth(  ) ) );
  }
}
