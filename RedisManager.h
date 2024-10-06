#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <thread>
#include <iostream>

#include "thirdparty/CRedisConn.h"

class RedisManager
{
public:
	void Init(std::string ip, uint32_t port)
	{
		if (Connect(ip, port) == false)
		{
			std::cout << "Redis connect 실패" << std::endl;
		}
	}

private:
	bool Connect(std::string ip, int port)
	{

	}
private:

	//현재 Redis용 WorkerThread를 동작 여부 bool 
	std::atomic<bool>	_isRun{ false };

	// thread -> jthread 사용  join (x)
	std::vector<std::jthread> workerThreads;

	//hiRedis
	RedisCpp::CRedisConn _connection;
};

