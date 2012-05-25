#pragma once

#include "PeerAgent.h"

class ClientAgent : public PeerAgent
{
public:
	ClientAgent(void);
	virtual ~ClientAgent(void);

	bool							Open(int io);
	void							Close();
	
private:
	int								m_io;
	int								m_timeout;
};

