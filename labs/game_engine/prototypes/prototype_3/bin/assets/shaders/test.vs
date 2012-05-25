
//cbuffer param 
//{
	//float4x4		world;
	//float4x4		view;
	//float4x4		proj;
//};


float4 VS( float3 Pos : POSITION ) : SV_POSITION
{
	float4 v;

	v.xyz = Pos.xyz;
	v.w = 1;

//	v = mul(v, world);
//
//	v = mul(v, view);

//	v = mul(v, proj);

	
	return v;

	//v = Pos * param.view * param.proj;

	//return float4(Pos.xyz, 1);
}
