#pragma once


/*
* ===================================================================
*				패킷 수신과 관련된 로직을 담당 (라이브러리단이 아니라, 컨텐츠 단)
* ===================================================================
*/

class PacketSession : public std::enable_shared_from_this<PacketSession>
{
public:
	PacketSession() = default;
	virtual ~PacketSession() = default;

public:
	using PacketHandler = std::function<void(std::shared_ptr<PacketSession>, char*, int)>;

	void RegisteHandler(int packetID, PacketHandler handler);

protected:
	std::unordered_map<int, PacketHandler> _handlers;
	virtual int OnRecvPacket(char* buffer, int len);
};

