#include <d3dx9.h>
namespace math
{
	inline
		void Vector2::Normalize()
	{
		D3DXVec2Normalize((D3DXVECTOR2*)this, (D3DXVECTOR2*)this);
	}

}
