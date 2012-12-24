

struct GBuffer
{
	half4	pos:SV_TARGET0;
	half4	normal:SV_TARGET1;
	half4	diff:SV_TARGET2;
};


float3 dr_light_dir(half3 n, half3 d)
{
	float c = max(0, dot(d, n));

	return float3(c, c, c);

}
