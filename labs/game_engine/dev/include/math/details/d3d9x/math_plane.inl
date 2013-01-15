#include <d3dx9.h>

namespace math
{
	inline	
		Plane::Plane(const Vector3& n, const Vector3& p)
	{
		D3DXPlaneFromPointNormal((D3DXPLANE*)this, (D3DXVECTOR3*)&p, (D3DXVECTOR3*)&n);
	}
	inline
		Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		D3DXPlaneFromPoints((D3DXPLANE*)this, (D3DXVECTOR3*)&p1, (D3DXVECTOR3*)&p2, (D3DXVECTOR3*)&p3);
	}
	inline
		void Plane::Normalize()
	{
		D3DXPlaneNormalize((D3DXPLANE*)this, (D3DXPLANE*)this);
	}
}