RasterizerState RS_Light
{
	CULLMODE = None;
};
BlendState BS_Light
{
	ALPHATOCOVERAGEENABLE				= false;
	BLENDENABLE[0]					= true;
	SRCBLEND					= ONE;
	DESTBLEND					= ONE;
	BLENDOP						= ADD;
	SRCBLENDALPHA					= ONE;
	DESTBLENDALPHA					= ONE;
	BLENDOPALPHA					= ADD;
	RENDERTARGETWRITEMASK[0]			= 0xF;
};
DepthStencilState DS_Light
{
	DepthEnable					= FALSE;
	DepthFunc					= LESS;
	DepthWriteMask					= ZERO;
	StencilEnable					= true;
	FrontFaceStencilFail				= KEEP;
	FrontFaceStencilDepthFail			= KEEP;
	FrontFaceStencilPass				= KEEP;
	FrontFaceStencilFunc				= EQUAL;

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail			= KEEP;
	BackFaceStencilPass				= KEEP;
	BackFaceStencilFunc				= NEVER;
};

struct DirectionalLight
{
	float3	dir;
	float	intensity;
	float3	clr;
	float	specular_pow;
};
struct PointLight
{
	float3	center;
	float	radius;
	float3	clr;

};

float3 dr_light_dir(half3 n, DirectionalLight light, float4x4 wv)
{
	float3 l = -mul(light.dir, (float3x3)wv);

	float il = max(0, dot(l, n)) * light.intensity;
	
	float3 v = float3(0, 0, -1);
	float3 h = (l + v ) /2;
	h = normalize(h);
	
	float3 r = reflect(-l, n);
	float s = max(0, dot(r, v));
	s = pow(s, light.specular_pow) * light.intensity;

	return il * light.clr + s * light.clr;
}

float3 dr_light_point(half4 p, half3 n, PointLight light, float4x4 wv)
{
	return float3(1, 1, 1);
}
