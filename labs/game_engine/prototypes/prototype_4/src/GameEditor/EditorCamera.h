#pragma once

class EditorCamera : public engine::BaseCamera
{
public:
	EditorCamera(void);
	virtual ~EditorCamera(void);

	void				Init();
	void				Update();

	math::Vector3		GetEyePos();
	math::Vector3		GetAxisZ();
	math::Vector3		GetAxisX();
	math::Vector3		GetAxisY();
	math::Vector3		IntersectXZPlane();
	void				OnMouseMove(UINT nFlags, CPoint point);
	void				OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void				OnMouseRButtonDown(UINT nFlags, CPoint point);
	void				OnMouseRButtonUp(UINT nFlags, CPoint point);


	void				SetViewPort(int cx, int cy);
private:
	float				RotationFactor();
	void				Rotate(int dx, int dy);
	void				Move(int dx, int dy);
	void				Zoom(int d);
	void				MoveAlignYZ(int dx, int dy);
private:

	int					m_vpw;
	int					m_vph;

	math::Matrix44		m_lastRotInvert;
	engine::ArcBall		m_arcBall;

	math::Matrix44		m_startViewMatrix;

};

