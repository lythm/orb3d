float4x4 mat:WORLDVIEWPROJ;

float3 dir = normalize(float3(1,-1, 1));

SamplerState diff[1]
{
    AddressU = Mirror;
    AddressV = Mirror;
};

struct vs_out
{
	float4 pos:POSITION;
	float4 clr:COLOR;
};

vs_out vs_main(float3 position:POSITION)
{
	vs_out vsout;
	vsout.pos = mul(float4(position, 1), mat);

	float3 n = normalize(position);
		
	float l = dot(n.xyz, -dir); 

	l = l + 0.3;
	vsout.clr = float4(l, l, l, 1);

	//vsout.clr = float4(1, 1, 1, 1);

	return vsout;
}

struct ps_out
{
	float4 color:COLOR;
};

ps_out ps_main(vs_out psin, uniform SamplerState decal : TEX0)
{
	ps_out psout;

	psout.color.xyz = psin.clr;
	psout.color.w = 1;
	return psout;
}

technique test
{
  pass p1
  {
	 // DepthTestEnable = false;
      AlphaBlendEnable = false;
      CullMode = None;
      FillMode = solid;

	  SetVertexShader( CompileShader( vs_4_0, vs_main() ) );
      SetPixelShader( CompileShader( ps_4_0, ps_main( diff[1] ) ) );

	  
  }
}
