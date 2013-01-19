#pragma once
class VoxelDemo
{
public:
	VoxelDemo();
	virtual ~VoxelDemo(void);

	bool										Init(ld3d::CoreApiPtr pCore);
	void										Release();
	void										Update();

	void										OnMsg(ld3d::EventPtr pEvent);
private:
	ld3d::CoreApiPtr							m_pCore;

	ld3d::CameraPtr								m_pCamera;

	ld3d::SoundChannelPtr						m_pChannel;
	ld3d::SoundPtr								m_pSound;
};

