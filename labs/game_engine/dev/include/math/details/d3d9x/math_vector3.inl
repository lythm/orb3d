#include <d3dx9.h>

namespace math
{

	inline
		void Vector3::Normalize()
	{
		D3DXVec3Normalize((D3DXVECTOR3*) this, (D3DXVECTOR3*)this);
	}

}