#pragma once
class VirtualScreen
{
public:
	VirtualScreen(void);
	virtual ~VirtualScreen(void);

	virtual void								Show();
	virtual void								Hide();
	virtual void								Update();
	virtual void								Render();



};

