#include "PacketSession.h"

int PacketSession::OnRecv(unsigned char* buffer, int len)
{
	int processLen = 0;

	while (true)
	{
		int dataSize = len - processLen;

		//header size 4
		if (dataSize < 4)
		{
			break;
		}

		// OnRecvPacket(&buffer[processLen],)

		// processLen += header.size();
	}

	return processLen;
}
