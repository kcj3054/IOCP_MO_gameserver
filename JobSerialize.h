#pragma once

#include <atomic>

class JobSerialize
{
private:
	//RefCountable* mOwner; // Owner ��ü (�������� addref/release ����)
	std::atomic<int> mRemainedJobCount = 0;
	//ThreadSafeQueue<Job> mJobQueue; // Job�� �����ϱ����� ������ ������ Queue

private:
	//job�� TSQ�� �߰�
	//inline void PushJob(Job* job) { mJobQueue.push(job); }

public:
	DoJob(Job* job)
	{
		//�ٸ� ������ �̹� ��ī��Ʈ�� �������״� 
		if (++mRemainedJobCount > 1)
		{
			PushJob(job);
		}
		else
		{
			//ó�� ���ε� �� 
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