#pragma once
class PeerAgent
{
public:

	typedef boost::signal<void (int, void*)>					PacketSignal;
	typedef boost::shared_ptr<PacketSignal>						PacketSignalPtr;
	typedef boost::unordered_map<int, PacketSignalPtr>			PacketHandlerMap;

	PeerAgent(void);
	virtual ~PeerAgent(void);


	virtual void												Update();

	virtual void												Send();
	
	
	void														AddHandler_ConnectionLost();
	void														AddHandler_UnknownPacket();
	void														AddHandler_Packet();

	void														SetHandler_KeepAlive();

private:
	int															m_io;
	int															m_timeout;

	boost::signal<void ()>										handler_keepalive;
	boost::signal<void (int err)>								handler_connection_lost;
	boost::signal<void (int eid, void* buffer)>					handler_unknown_packet;

	PacketHandlerMap											m_packetHandlers;

};

