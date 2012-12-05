#pragma once

namespace engine
{
	class EXPORT_CLASS MeshUtil
	{
	public:

		
		static MeshPtr						CreateSphere(float radius, float slice, float stack, MaterialPtr pMat);

	private:
		MeshUtil(void);
		virtual ~MeshUtil(void);


	};


}