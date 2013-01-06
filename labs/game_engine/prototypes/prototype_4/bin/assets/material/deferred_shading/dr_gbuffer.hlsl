struct GBuffer
{
	half4	T1:SV_TARGET0;
	half4	T2:SV_TARGET1;
	half4	T3:SV_TARGET2;
};



SamplerState Sampler_GBuffer
{
	AddressU = clamp;
	AddressV = clamp;

	filter = MIN_MAG_MIP_POINT ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};
SamplerState Sampler_GBufferNormal
{
	AddressU = clamp;
	AddressV = clamp;

	filter = MIN_MAG_MIP_LINEAR ;
	BorderColor = float4(1,0,0,1);
	MinLod = 0;
	MaxLod = 0;
};

GBuffer dr_gbuffer_compose(half4 p, half3 n, half3 d, half s)
{
	GBuffer g;
	g.T1 = p;
	g.T2 = half4(n, 1);
	g.T3 = half4(d, s);

	return g;
}

half3 dr_gbuffer_get_normal(Texture2D<half4> g[3], float2 uv)
{
	half3 normal = g[1].Sample(Sampler_GBufferNormal, uv).xyz;

	normal = normalize(normal);
	
	return normal;
}
half4 dr_gbuffer_get_position(Texture2D<half4> g[3], float2 uv)
{
	half4 p = g[0].Sample(Sampler_GBuffer, uv);
	return p;
}
half3 dr_gbuffer_get_diffuse(Texture2D<half4> g[3], float2 uv)
{
	half4 c = g[2].Sample(Sampler_GBuffer, uv);
	return c.xyz;
}
half dr_gbuffer_get_specular_power(Texture2D<half4> g[3], float2 uv)
{
	half4 c = g[2].Sample(Sampler_GBuffer, uv);
	return c.w;
}
