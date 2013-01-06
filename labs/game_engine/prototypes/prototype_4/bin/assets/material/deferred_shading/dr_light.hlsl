RasterizerState RS_Light
{
	CULLMODE = back;
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
	DepthEnable						= FALSE;
	DepthFunc						= LESS;
	DepthWriteMask					= ZERO;
	StencilEnable					= true;
	FrontFaceStencilFail			= KEEP;
	FrontFaceStencilDepthFail		= KEEP;
	FrontFaceStencilPass			= KEEP;
	FrontFaceStencilFunc			= EQUAL;

	BackFaceStencilFail				= KEEP;
	BackFaceStencilDepthFail		= KEEP;
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
	float3	clr;
	float	intensity;
	float	radius;
	float	specular_pow;
};

struct SpotLight
{
	float	range;
};

float3 dr_light_dir(half3 n, DirectionalLight light, float4x4 wv)
{
	float3 l = -mul(light.dir, (float3x3)wv);

	float il = max(0, dot(l, n)) * light.intensity;
	
	float3 v = float3(0, 0, -1);
		
	float3 r = reflect(-l, n);
	float s = max(0, dot(r, v));
	s = pow(s, light.specular_pow) * light.intensity;

	return il * light.clr + s * light.clr;
}

float3 dr_light_point(float3 p, half3 n, PointLight light, float4x4 wv)
{
	float3 center = mul(float4(0, 0, 0, 1), wv).xyz;
	
	float3 l = p - center;
	float d = length(l);
	l = -normalize(l);

	float falloff = 1;
	float att = 1 - saturate(d * falloff / light.radius);

	float il = max(0, dot(l , n)) * light.intensity * att;

	float3 v = float3(0, 0, -1);
		
	float3 r = reflect(-l, n);
	float s = max(0, dot(r, v));
	s = pow(s, light.specular_pow) * light.intensity * att;

	return il * light.clr + s * light.clr;

	//return float3(1, 1, 1);
}


float3 dr_light_spot()
{
	return float3(1, 1, 1);
}