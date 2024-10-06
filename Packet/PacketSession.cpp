#include "PacketSession.h"

void PacketSession::RegisteHandler(int packetID, PacketHandler handler)
{
	_handlers[packetID] = handler;
}

/*
* 딱 정확한 단위의 패킷이 왔을 때 OnRecvPacket이 호출 됌
*/
int PacketSession::OnRecvPacket(char* buffer, int len)
{
    int32_t packetId = 0 /* 패킷 ID 추출 로직 */;
    auto iter = _handlers.find(packetId);
    if (iter != _handlers.end())
    {
        iter->second(shared_from_this(), buffer, len);
    }
    else
    {
        // 기본 처리 로직
    }

    return 0;
}
