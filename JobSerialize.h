#pragma once

#include <atomic>

class JobSerialize
{
private:
	//RefCountable* mOwner; // Owner 객체 (소유자의 addref/release 목적)
	std::atomic<int> mRemainedJobCount = 0;
	//ThreadSafeQueue<Job> mJobQueue; // Job을 관리하기위한 스레드 세이프 Queue

private:
	//job을 TSQ에 추가
	//inline void PushJob(Job* job) { mJobQueue.push(job); }

public:
	DoJob(Job* job)
	{
		//다른 곳에서 이미 잡카운트를 증가시켰다 
		if (++mRemainedJobCount > 1)
		{
			PushJob(job);
		}
		else
		{
			//처음 바인딩 됌 
			PushJob(job);
		}
	}
};



// DoSerialize
// 

public:
	template<typename TFuncOwner, MemberFunction TFunc, JobParamConcepT... args>
	bool DoSerialize()
	{
		auto job = xnew<>();

		return mJobserializer.DoJob(job);
	}
	..