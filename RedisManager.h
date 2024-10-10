#pragma once

#include "pch.h"

#include "thirdparty/CRedisConn.h"

#include "RedisDefine.h"

class RedisManager
{
public:
	void Init(std::string ip, uint32_t port, uint32_t threadCount)
	{
		//Redis 연결 
		if (_connection.connect(ip, port) == false)
		{
			std::cout << "Redis connect 실패" << std::endl;
			
			return;
		}

		//atomic
		_isRun = true;

		//Redis관련 Task 처리 용 WorkerThread 생성 
		for (int i = 0; i < threadCount; ++i)
		{
			// 캡처에 this! 
			workerThreads.emplace_back([this]() {
				TaskProcessThread();
				});
		}
	}

private:
	
	// Redis관련 Task 처리 용 WorkerThread
	void TaskProcessThread()
	{
		std::cout << "Redis worker Thread 가동\n"; 

		while (_isRun)
		{
			if (auto optTask = TakeRequestTask(); optTask.has_value())
			{
				auto task = optTask.value();

				// switch case나 if문이 아닌 unordered_map으로 변경 길이가 길어질 수록 보기에 안좋다 
				// if(task.packetID == )
			
				//todo 여기서 invoke.! 
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	std::optional<RedisTask> TakeRequestTask()
	{
		std::lock_guard guard(_reqLock);

		if (_requestTask.empty())
		{
			return std::nullopt;
		}
		
		auto task = _requestTask.front();
		_requestTask.pop_front();

		return task;
	}

	void PushResponse(RedisTask task)
	{
		std::scoped_lock<std::mutex> guard(_resLock);

		_responseTask.push_back(task);
	}
	
private:

	//현재 Redis용 WorkerThread를 동작 여부 bool 
	std::atomic<bool>	_isRun{ false };

	// thread -> jthread 사용  join (x)
	std::vector<std::jthread> workerThreads;

	std::mutex _reqLock;
	std::mutex _resLock;
	std::deque<RedisTask> _requestTask;
	std::deque<RedisTask> _responseTask;

	//hiRedis
	RedisCpp::CRedisConn _connection;

	//redis Task에 대한 std::function 
	std::unordered_map <RedisPacketID, std::is_function<void(RedisTask&)>> _taskCallback;
};

