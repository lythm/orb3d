#pragma once

class EditorCamera : public ld3d::Camera
{
public:
	EditorCamera(void);
	virtual ~EditorCamera(void);

	void				Init(ld3d::CoreApiPtr);
	void				Update();

	math::Vector3		GetEyePos();
	math::Vector3		GetFocusPos();
	math::Vector3		GetAxisZ();
	math::Vector3		GetAxisX();
	math::Vector3		GetAxisY();
	math::intersect_ret IntersectXZPlane(math::Vector3& target);
	void				OnMouseMove(UINT nFlags, CPoint point);
	void				OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void				OnMouseRButtonDown(UINT nFlags, CPoint point);
	void				OnMouseRButtonUp(UINT nFlags, CPoint point);
	
	void				SetViewPort(int cx, int cy);

	math::Ray			PickRay(int x, int y);

	void				SetFocusPos(const math::Vector3& at);
	void				SetEyePos(const math::Vector3& eye);
private:
	
	void				Rotate(int dx, int dy);
	void				Zoom(int d);
	void				Move(int dx, int dy);
private:

	int					m_vpw;
	int					m_vph;

	math::Vector3		m_at;
	math::Vector3		m_eye;

	ld3d::CoreApiPtr	m_pCore;

};

