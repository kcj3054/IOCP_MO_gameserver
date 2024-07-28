#pragma once

#include "Session.h"

class PacketSession : public Session
{
public:
	PacketSession() = default;
	virtual ~PacketSession() = default;

protected:
	virtual int OnRecv(unsigned char* buffer, int len) sealed;
	virtual int OnRecvPacket(unsigned char* buffer, int len) abstract;
};

