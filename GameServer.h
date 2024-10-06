#pragma once
#include "../IOCPServer/ServerNetwork/IOCPServer.h"
#include "../IOCPServer/Packet/Packet.h"
#include "../IOCPServer/Packet/packetType.h"
#include "../IOCPServer/Packet/PacketSession.h"
#include "../IOCPServer/Packet/PaketManager.h"

#include <concurrent_queue.h>

#include <functional>
#include <unordered_map>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>


class GameServer : public IOCPServer
{
public:
	GameServer() = default;
	virtual ~GameServer() = default;
	
	void RegisterPackets()
	{
		/*mPacketHandlers[PACKET_TYPE_LOGIN] = [this](const PacketData& packet) { HandleLogin(packet); };
		mPacketHandlers[PACKET_TYPE_LOGOUT] = [this](const PacketData& packet) { HandleLogout(packet); };
		mPacketHandlers[PACKET_TYPE_MESSAGE] = [this](const PacketData& packet) { HandleMessage(packet); };*/
	}

	virtual void OnConnect(const UINT32 clientIndex_) final
	{
		printf("[OnConnect] 클라이언트: Index(%d)\n", clientIndex_);
	}

	virtual void OnClose(const UINT32 clientIndex_) final 
	{
		printf("[OnClose] 클라이언트: Index(%d)\n", clientIndex_);
	}
	
	//문제가 있음 패킷은 단위 단위로 오지 않음..
	//IOCPServer.h 부분에  Packet을 분할하는 부분을 추가할 예정  
	virtual void OnReceive(const UINT32 clientIndex_, const UINT32 size_, char* pData_) final
	{
		printf("[OnReceive] 클라이언트: Index(%d), dataSize(%d)\n", clientIndex_, size_);

		//PacketData packet;
		//packet.Set(clientIndex_, size_, pData_);


		//// ConcurrentQueue를 사용하여 lock부분 제거 
		//mPacketDataQueue.push(packet); 

		//// todo 생각을 해보자.. 굳이 OnRecv한 뒤 -> PacketManger -> 다시 할 이유가 있을까 ? 나중에 다시 정리 하기
		////PacketManger 영역 단 
		//packetManger->ReceivePacketData(clientIndex_, size_, pData_);
	}

	/*
	* Packet처리용 스레드와 IO 담당 스레드들을 분리.
	*/

	void Run(const UINT32 maxClient)
	{
		mIsRunProcessThread = true;
		mProcessThread = std::thread([this]() { ProcessPacket(); });

		StartServer(maxClient);
	}

	void End()
	{
		mIsRunProcessThread = false;

		if (mProcessThread.joinable())
		{
			mProcessThread.join();
		}

		DestroyThread();
	}

private:
	void ProcessPacket()
	{
		while (mIsRunProcessThread)
		{
			auto packetData = DequePacketData();
			if (packetData.DataSize != 0)
			{
				SendMsg(packetData.SessionIndex, packetData.DataSize, packetData.pPacketData);
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
	}
	PacketData DequePacketData()
	{
		PacketData packetData;
		if (mPacketDataQueue.try_pop(packetData))
		{
			return packetData;
		}
		else
		{
			return PacketData();
		}
	}

private:

	bool mIsRunProcessThread = false;

	std::thread mProcessThread;

	std::mutex mLock;
	concurrency::concurrent_queue<PacketData> mPacketDataQueue;

	//삭제 
	std::unordered_map<int, std::function<void(const PacketData&)>> mPacketHandlers;

private:
	std::unique_ptr<PaketManager> packetManger = std::make_unique<PaketManager>();
};