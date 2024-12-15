#pragma once

#include "Packet.h"

class RedisManager;

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

	//=====================Redis==========================================
	// std::unique_ptr<RedisManager> _redisManager;


	//=====================RedisEnd=======================================
	using PROCESS_RECV_PACKET_FUNCTION = std::function<void(PaketManager&, UINT32, UINT16, char*)>; 

	std::unordered_map<int, PROCESS_RECV_PACKET_FUNCTION> recvFunctionDictionary;

	/*
	* 	std::deque<UINT32> mInComingPacketUserIndex;
	std::deque<PacketInfo> mSystemPacketQueue;
	�������� �ΰ��� �� ���������� �ϳ��� PacketQueue�� �ϸ� �� �ܼ������������� ?. .
	*/

	concurrency::concurrent_queue<UINT32> comingPacketUserIndex;
};


/*
redis 

- key - value ���� 

- 

- mmorpg���� �κ� ������ ��ġ �ű�� ���� �ϳ��ϳ� rdb�� �����ϴ� ���� ���ذ� ũ��.
	-	�ش� ��ġ �Űܰ��� �͵��� redis�� ĳ���� �� �� �α׾ƿ��� �� �� rdbms�� �����ϴ� ����� �����Ѵ�. 
	-	

- 1 ������
- ��û�� atomic�ϰ� ó���Ѵ� 
- �ֽ� ���������� ��Ƽ������ ���������� �뵵�� �ٸ� 
	- �츮�� �����ϴ� ��Ƽ������� �ƴϴ�. 

- String, Lists, Sets, 
- Expires (redis�� �� key���� ���� �ð��� �������� �� �ִ�)
	- �޸� ���� ������ ������ �� ���� 

- pub / sub 
	- Ȯ���غ��� 

-  
*/

/*
* [boost.asio]�� �ʿ��� redis ���̺귯�� 
* 
* - redisclient 
* - boost.asio(header only) based redis-client library.
* - c++11 
* - linux, windows ���� 
*/

/*
* ��� �� 
* 
* [�α��� ����]
*	-> �α��� ������ ������ ���� ��� ������ ���� �� �˷��ش�.
* �̷� �� ��� ���Ӽ������� �α��μ����� �ٰ����� ��� �α��� ������ ���� �� ���������� �߻��Ѵ�.
* 
* -> redis�� �̿��ϸ� ���������� ���� �� �ִ�. 
* 
* 
* [ĳ�� �뵵]
* - �������� db������ ĳ�� �뵵�� ����ߴ�. �׷����� db������ ������ ĳ���� ���ư��� ������ �߻���
* 
* 
* [��ŷ]
* - �ǽð� ��ŷ �� rdb�� ���ϰ� ���ϴ� .
* - �׷� ������ ������ ���� ��ŷ ����. ���
* 
* - redis�� �̿��ϸ� �ǽð� ��ŷ ������ ������� ����. 
* - 
*/