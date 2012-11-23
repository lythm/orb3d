#include "StdAfx.h"
#include "EditorCamera.h"
#include "AppContext.h"


EditorCamera::EditorCamera(void)
{
	m_vpw				= 800;
	m_vph				= 600;

	m_lastRotInvert.MakeIdentity();
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
math::Vector3 EditorCamera::GetAxisZ()
{
	using namespace math;
	const Matrix44& view = GetViewMatrix();

	return view.GetCol3(2);
}
math::Vector3 EditorCamera::GetAxisX()
{
	using namespace math;
	const Matrix44& view = GetViewMatrix();

	return view.GetCol3(0);
}
math::Vector3 EditorCamera::GetAxisY()
{
	using namespace math;
	const Matrix44& view = GetViewMatrix();

	return view.GetCol3(1);
}
void EditorCamera::OnMouseMove(UINT nFlags, CPoint point)
{



	using namespace math;


	//
	/*if(MK_RBUTTON & nFlags)
	{


	MeshRenderer::instance()->mouseMoveCam(delta.x, delta.y);
	}*/

	static CPoint lastpt = point;
	CPoint delta = point - lastpt;

	if(MK_RBUTTON & nFlags)
	{
		m_arcBall.Move(point.x, point.y);

		math::Matrix44 r = m_arcBall.GetRotationMatrix();
		
		math::Matrix44 view = GetViewMatrix();

		view = r * (m_lastRotInvert * view) ;

		SetViewMatrix(view);

		m_lastRotInvert = r;
		m_lastRotInvert.Invert();
		//Rotate(delta.x, delta.y);
	}
	if(MK_MBUTTON & nFlags)
	{

		MoveAlignYZ(delta.x, delta.y);

	}
	lastpt = point;
}
void EditorCamera::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	Zoom(zDelta);
}
math::Vector3 EditorCamera::IntersectXZPlane()
{
	using namespace math;

	Ray r(GetEyePos(), GetAxisZ());
	Plane p(Vector3(0, 1, 0), Vector3(0, 0, 0));

	Real t = 0;
	RayIntersectPlane(r, p, t);

	Vector3 target = r.GetPos(t);

	return target;
}
void EditorCamera::SetViewPort(int cx, int cy)
{
	using namespace math;

	m_vpw = cx;
	m_vph = cy;
	float aspect = float(m_vpw) / float(m_vph);
	m_arcBall.SetViewPort(cx, cy);
	PerspectiveFovLH(1.0f/ 4.0f * MATH_PI, aspect, 0.001, 10000000);

}
void EditorCamera::Rotate(int dx, int dy)
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 axis_x = GetAxisX();
	Vector3 axis_z = GetAxisZ();
	Vector3 axis_y = GetAxisY();

	Vector3 t = IntersectXZPlane();

	Real el = (e - t).Length();

	float factor = RotationFactor();

	e = e - t;

	Matrix44 rot = MatrixRotationAxis(axis_y, dx * factor);

	rot = rot * MatrixRotationAxis(axis_x, dy * factor);

	TransformCoord(e, rot);

	e += t;

	LookAtLH(e, t, Vector3(0, 1, 0));
}
void EditorCamera::Move(int dx, int dy)
{
}
void EditorCamera::Zoom(int d)
{
	using namespace math;

	Vector3 e = GetEyePos();

	Vector3 t = IntersectXZPlane();

	Vector3 v = e - t;
	Real l = v.Length();

	l -= d * l * 0.001;

	l = l <= 0.1 ? 0.1 : l;

	v.Normalize();

	v *= l;

	e = t + v;

	LookAtLH(e, t, Vector3(0, 1, 0));
}
void EditorCamera::MoveAlignYZ(int dx, int dy)
{
	using namespace math;

	Matrix44 view = GetViewMatrix();

	Vector3 e = GetEyePos();
	Vector3 t = IntersectXZPlane();

	TransformCoord(t, view);
	TransformCoord(e, view);
	view.Invert();

	Vector3 p(-dx * 0.1, dy * 0.1, 0);

	t += p;
	e += p;

	TransformCoord(t, view);
	TransformCoord(e, view);

	LookAtLH(e, t, Vector3(0, 1, 0));
}
float EditorCamera::RotationFactor()
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 t = IntersectXZPlane();

	Real el = (e - t).Length();

	return log(el);
}

void EditorCamera::OnMouseRButtonDown(UINT nFlags, CPoint point)
{
	m_arcBall.Begin(point.x, point.y);
}
void EditorCamera::OnMouseRButtonUp(UINT nFlags, CPoint point)
{
	m_arcBall.End();
}
