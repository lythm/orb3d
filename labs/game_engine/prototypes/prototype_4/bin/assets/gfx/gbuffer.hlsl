

struct GBuffer
{
	half4	pos;
	half4	Normal;
	half4	diff;
};

void gbuffer_render_vpos(inout GBuffer buffer, float3 pos, float4x4 wv)
{
	buffer.pos = mul(float4(pos, 1), wv);
}
void gbuffer_render_vnormal(inout GBuffer buffer, float3 normal, float4x4 wv)
{
	buffer.normal = mul(float4(normal, 0), wv);
}
void gbuffer_render_diff(inout GBuffer buffer, float4 clr, float specular)
{
	
}
