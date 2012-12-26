#pragma once

namespace engine
{
	class EXPORT_CLASS MeshUtil
	{
	public:

		static MeshPtr						CreatePlane(float size, MaterialPtr pMat);
		static MeshPtr						CreateSphere(float radius, float slice, float stack, MaterialPtr pMat);
		static MeshPtr						CreateCube(float size, MaterialPtr pMat);
		static MeshPtr						CreateCone(float range, float angle, float slice, MaterialPtr pMat);
		
		
		static GPUBufferPtr					CreateSphere(Sys_GraphicsPtr pGraphics, float radius, float slice, float stack, int& nVerts);
		static GPUBufferPtr					CreateSpotLightCone(Sys_GraphicsPtr pGraphics, float range, float angle, float slice, int& nVerts);
	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);


	};
}
