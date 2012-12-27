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
	float3 dir;
	float3 clr;
};
struct PointLight
{
	float3	center;
	float	radius;
	float3	clr;

};

float3 dr_light_dir(half3 n, DirectionalLight light, float4x4 wv)
{
	float3 d = -mul(light.dir, (float3x3)wv);

	//d = normalize(d);

	float il = max(0, dot(d, n));
	
	return il * light.clr;

}

float3 dr_light_point(half4 p, half3 n, PointLight light, float4x4 wv)
{
	return float3(1, 1, 1);
}
