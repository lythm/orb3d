#pragma once

class EditorCamera : public engine::BaseCamera
{
public:
	EditorCamera(void);
	virtual ~EditorCamera(void);

	void				Update();

	math::Vector3		GetEyePos();
	math::Vector3		GetOri();
	math::Vector3		IntersectXZPlane();
	void				OnMouseMove(UINT nFlags, CPoint point);

	void				SetViewPort(int cx, int cy);
private:

	int					m_vpw;
	int					m_vph;

};

