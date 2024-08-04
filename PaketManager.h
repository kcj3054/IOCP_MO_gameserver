#pragma once

#include <Windows.h>

#include "Packet.h"

#include <functional>
#include <thread>
#include <mutex>

#include <concurrent_queue.h>

class PaketManager
{
public:
	PaketManager() = default;
	~PaketManager();

	void Init(const int maxClinet);

	bool Run();

	void ReceivePacketData(const unsigned int clientIndex, const unsigned int size, char* data);

	void PushSystemPacket(PacketInfo packet);


private:
	void CreateClient();

	void EnqueuePacketData(const int clientIndex);

	PacketInfo DequePacketData();

	void ProcessPacket();

private:
	
	void ProcessUserConnect(UINT32 clientIndex, UINT16 packetSize, char* packet);

private:

	std::mutex lock;
	bool isRunProcessThread = false;
	std::thread processThread;

	using PROCESS_RECV_PACKET_FUNCTION = std::function<void(PaketManager&, UINT32, UINT16, char*)>; 

	std::unordered_map<int, PROCESS_RECV_PACKET_FUNCTION> recvFunctionDictionary;

	/*
	* 	std::deque<UINT32> mInComingPacketUserIndex;
	std::deque<PacketInfo> mSystemPacketQueue;
	느낌으로 두개로 할 수도있지만 하나의 PacketQueue로 하면 더 단순해지지않을까 ?. .
	*/

	concurrency::concurrent_queue<UINT32> comingPacketUserIndex;
};

