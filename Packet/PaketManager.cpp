#include "../pch.h"
#include "PaketManager.h"

// #include "../RedisManager.h"

PaketManager::~PaketManager()
{
	isRunProcessThread = false;

	if (processThread.joinable())
	{
		processThread.join();
	}
}

void PaketManager::Init(const int maxClinet)
{
	//Handler 등록
	// recvFunction

	//User생성도 가능 
	// CreateComponent -> client
	recvFunctionDictionary[(int)PacketID::LOGIN_REQUEST] = &PaketManager::ProcessUserConnect;


	isRunProcessThread = true;
	processThread = std::thread(&PaketManager::ProcessPacket, this);


	//===================Redis=====================================
	// _redisManager = std::make_unique<RedisManager>();
}

bool PaketManager::Run()
{
	//RedisManager 시작 , todo : 하드 코딩 부분 제거하기 
	// _redisManager->Init("127.0.0.1", 6379, 10);

	return false;
}

void PaketManager::ReceivePacketData(const unsigned int clientIndex, const unsigned int size, char* data)
{
	//RingBuffer를 이용하여 Packet조립 후 Queue에 Packet을 넣음 
	// -> UserManager들도 Packet을 가지고 있고, auto pUser -> SetPacketData()로 패킷들을 조립

	//todo : 굳이 여기서 lock을 할 필요가 있을까? ... -> Engine단에서 lock을 사용하는 것을 추천 
	EnqueuePacketData(clientIndex);
}

void PaketManager::PushSystemPacket(PacketInfo packet)
{

}

void PaketManager::CreateClient()
{
	// UserManager 생성 후 -> UserManager Init;;
}

//해당 함수에 Enqueue된 패킷은 조립이 완성된 패킷 
void PaketManager::EnqueuePacketData(const int clientIndex)
{
	std::lock_guard<std::mutex> lockGuard(lock);

}

PacketInfo PaketManager::DequePacketData()
{
	return PacketInfo();
}

void PaketManager::ProcessPacket()
{
	while (isRunProcessThread)
	{
		//redis쪽인지 db쪽 패킷 처리인지, 일반 네트워크 Packe 처리인지 구분이 중요하다 
		if (auto packetData = DequePacketData(); packetData.packetID != 0)
		{
			//여기서 바로 recvFunctionDictionary.find로 찾는 것도 좋은 듯 
			//end존재하는 packet이라면 바로 실행 

			if (auto contentsPacket = recvFunctionDictionary.find(packetData.packetID); contentsPacket != recvFunctionDictionary.end())
			{
				contentsPacket->second(*this, packetData.cliendtIndex, packetData.dataszie, packetData.packet);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void PaketManager::ProcessUserConnect(UINT32 clientIndex, UINT16 packetSize, char* packet)
{

}
