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

	static CPoint lastpt = point;
	CPoint delta = point - lastpt;

	if(MK_RBUTTON & nFlags && MK_CONTROL & nFlags)
	{
		Rotate(delta.x, delta.y);
	}
	if(MK_MBUTTON & nFlags)
	{
		Move(delta.x, delta.y);
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
	PerspectiveFovLH(1.0f/ 4.0f * MATH_PI, aspect, 0.001f, 10000000);

}
void EditorCamera::Rotate(int dx, int dy)
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 axis_x = GetAxisX();
	Vector3 axis_y = GetAxisY();

	Vector3 t = IntersectXZPlane();

	float factor = 0.5f / 108.0f;
	e = e - t;
	Matrix44 rot = MatrixRotationAxisY(dx * factor);

	rot = MatrixRotationAxis(axis_x, dy * factor) * rot;

	TransformCoord(e, rot);

	e += t;
	
	TransformNormal(axis_y, rot);

	LookAtLH(e, t, axis_y);
}

void EditorCamera::Zoom(int d)
{
	using namespace math;

	Vector3 e = GetEyePos();
	Vector3 t = IntersectXZPlane();
	Vector3 up = GetAxisY();

	Vector3 v = e - t;
	
	Real l = v.Length();

	Real offset = d /120.0f * l * 0.2f;

	l -= offset;

	l = l <= 1.0f ? 1.0f : l;

	v.Normalize();

	v *= l;

	e = t + v;

	LookAtLH(e, t, up);

}
void EditorCamera::Move(int dx, int dy)
{
	using namespace math;

	Matrix44 view = GetViewMatrix();

	Vector3 e = GetEyePos();
	Vector3 t = IntersectXZPlane();

	TransformCoord(t, view);
	TransformCoord(e, view);
	view.Invert();

	Vector3 p(-dx * 0.5f, dy * 0.5f, 0);

	t += p;
	e += p;

	TransformCoord(t, view);
	TransformCoord(e, view);

	LookAtLH(e, t, Vector3(0, 1, 0));
}


void EditorCamera::OnMouseRButtonDown(UINT nFlags, CPoint point)
{

}
void EditorCamera::OnMouseRButtonUp(UINT nFlags, CPoint point)
{

}

void EditorCamera::Init()
{
	using namespace math;

	LookAtLH(Vector3(0, 150, -150), Vector3(0, 0, 0), Vector3(0, 1, 0));

}
math::Ray EditorCamera::PickRay(int x, int y)
{
	using namespace math;

	return UnProject(x, y, m_vpw, m_vph, MatrixIdentity(), GetViewMatrix(), GetProjMatrix());
}
