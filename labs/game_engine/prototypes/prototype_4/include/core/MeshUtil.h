#pragma once

namespace engine
{
	class EXPORT_CLASS MeshUtil
	{
	public:

		
		static MeshPtr						CreateSphere(float radius, float slice, float stack, MaterialPtr pMat);
		static MeshPtr						CreateCube(float size, MaterialPtr pMat);
	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);


	};


}