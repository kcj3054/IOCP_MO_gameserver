#pragma once

#include <Windows.h>
#include <functional>
#include <concurrent_queue.h>
#include <mutex>
#include <memory>

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
	느낌으로 두개로 할 수도있지만 하나의 PacketQueue로 하면 더 단순해지지않을까 ?. .
	*/

	concurrency::concurrent_queue<UINT32> comingPacketUserIndex;


	
};


/*
redis 

- key - value 형태 

- 

- mmorpg에서 인벤 아이템 위치 옮기는 것을 하나하나 rdb에 저장하는 것은 손해가 크다.
	-	해당 위치 옮겨가는 것들은 redis에 캐싱을 한 뒤 로그아웃을 할 때 rdbms에 저장하는 방법도 존재한다. 
	-	

- 1 스레드
- 요청을 atomic하게 처리한다 
- 최신 버전에서는 멀티스레드 지원하지만 용도가 다름 
	- 우리가 생각하는 멀티스레드는 아니다. 

- String, Lists, Sets, 
- Expires (redis의 각 key에는 만기 시각을 설정해줄 수 있다)
	- 메모리 부족 현상을 막아줄 수 있음 

- pub / sub 
	- 확인해보기 

-  
*/

/*
* [boost.asio]가 필요한 redis 라이브러리 
* 
* - redisclient 
* - boost.asio(header only) based redis-client library.
* - c++11 
* - linux, windows 지원 
*/

/*
* 사용 예 
* 
* [로그인 서버]
*	-> 로그인 서버에 인증을 한후 어디 서버로 붙을 지 알려준다.
* 이럴 때 모든 게임서버들이 로그인서버에 붙고잇을 경우 로그인 서버가 죽을 때 병목현상이 발생한다.
* 
* -> redis를 이용하면 병목현상을 막을 수 있다. 
* 
* 
* [캐싱 용도]
* - 예전에는 db서버를 캐싱 용도로 사용했다. 그렇지만 db서버가 죽으면 캐싱이 날아가는 문제가 발생함
* 
* 
* [랭킹]
* - 실시간 랭킹 시 rdb에 부하가 심하다 .
* - 그런 이유로 월요일 새벽 랭킹 갱신. 등등
* 
* - redis를 이용하면 실시간 랭킹 구현에 어려움이 없음. 
* - 
*/