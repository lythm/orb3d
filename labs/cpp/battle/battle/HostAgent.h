#pragma once


class HostAgent
{
public:
	HostAgent(void);
	virtual ~HostAgent(void);

	bool							Open(int addr);
	void							Close();
	
	void							AddHandler_Connected();
private:
	int								m_addr;
	int								m_retryInterval;

	boost::signal<void ()>			handler_connected;


};

