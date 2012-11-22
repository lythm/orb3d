#include "StdAfx.h"
#include "EditorCamera.h"
#include "AppContext.h"


EditorCamera::EditorCamera(void)
{
	m_vpw				= 800;
	m_vph				= 600;
}


EditorCamera::~EditorCamera(void)
{
}
void EditorCamera::Update()
{
	using namespace engine;
	RenderSystemPtr pRS = AppContext::GetCoreApi()->GetRenderSystem();

	pRS->SetViewMatrix(GetViewMatrix());
	pRS->SetProjMatrix(GetProjMatrix());

	math::Vector3 t = IntersectXZPlane();
	return;
}
math::Vector3 EditorCamera::GetEyePos()
{
	using namespace math;
	Matrix44 view = GetViewMatrix();

	view.Invert();

	Vector3 e(0,0,0);

	TransformCoord(e, view);
	return e;
}
math::Vector3 EditorCamera::GetOri()
{
	using namespace math;
	const Matrix44& view = GetViewMatrix();

	return view.GetCol3(2);
}
void EditorCamera::OnMouseMove(UINT nFlags, CPoint point)
{
	
	static CPoint lastpt = point;
	CPoint delta = point - lastpt;


	using namespace math;

	
	//
	/*if(MK_RBUTTON & nFlags)
	{
		
		
		MeshRenderer::instance()->mouseMoveCam(delta.x, delta.y);
	}*/
	if(MK_LBUTTON & nFlags)
	{
		Vector3 e = GetEyePos();
		Vector3 o = GetOri();
		Vector3 t = IntersectXZPlane();

		Real el = e.Length();
	
	////float speed = MeshRenderer::instance()->getCamera()->getDistanceToTarget() * 0.005;
		float speed = el;// * 10;
		
		Ray r1 = UnProject(lastpt.x, lastpt.y, m_vpw, m_vph, MatrixIdentity(), GetViewMatrix(), GetProjMatrix());
		
		Ray r2 = UnProject(point.x, point.y, m_vpw, m_vph, MatrixIdentity(), GetViewMatrix(), GetProjMatrix());

		Vector3 v = (r2.o + r2.d - t) - (r1.o + r1.d - t);

		e = e - t;
		e = e - v * speed;

		e.Normalize();
		
		e = e * el;

		e = e + t;

		LookAtLH(e, t, Vector3(0, 1, 0));
		
	}
	
	lastpt = point;
}
math::Vector3 EditorCamera::IntersectXZPlane()
{
	using namespace math;

	Ray r(GetEyePos(), GetOri());
	Plane p(Vector3(0, 1, 0), Vector3(0, 0, 0));

	Real t = 0;
	RayIntersectPlane(r, p, t);

	Vector3 target = r.GetPos(t);

	return target;
}
void EditorCamera::SetViewPort(int cx, int cy)
{
	m_vpw = cx;
	m_vph = cy;
}