#include <d3dx9.h>
namespace math
{
	inline
		void Quat::Invert()
	{
		D3DXQuaternionInverse((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
	}
	inline
		const Quat& Quat::operator*=(const Quat& rhs)
	{
		D3DXQuaternionMultiply((D3DXQUATERNION*)this, (D3DXQUATERNION*)this, (D3DXQUATERNION*)&rhs);
		return *this;
	}
	inline
		void Quat::Normalize()
	{
		D3DXQuaternionNormalize((D3DXQUATERNION*)this, (D3DXQUATERNION*)this);
	}
}