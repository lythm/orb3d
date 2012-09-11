#include <d3dx9.h>
namespace math
{
	inline
		void Vector4::Normalize()
	{
		D3DXVec4Normalize((D3DXVECTOR4*) this, (D3DXVECTOR4*)this);
	}


}