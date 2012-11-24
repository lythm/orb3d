
float4x4 world:MATRIX_WORLD;
float4x4 view:MATRIX_VIEW;
float4x4 proj:MATRIX_PROJ;
float4x4 wvp:MATRIX_WVP;

struct vs_in
{
	float3 pos:POSITION;
};
struct vs_out
{
	float4 pos:SV_POSITION;
};

vs_out vs_main(vs_in vsin)
{
	vs_out vsout;
	vsout.pos = mul(float4(vsin.pos, 1), wvp);
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

RasterizerState rs
{
	CULLMODE = None;
	FILLMODE=SOLID;
};
technique11 test
{
  pass p1
  {
	//rs.FILLMODE=wireframe;
	SetRasterizerState(rs);
	SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
	SetPixelShader( CompileShader( ps_4_0, ps_main(  ) ) );
  }
}