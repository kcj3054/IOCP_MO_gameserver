#pragma once
class Job
{
public:
	enum class JobType : unsigned short
	{
		GLOBAL,
		FUTURE,
		CALLBACK,
		TIMER,
		SERIALIZE
	};

protected:
	explicit Job(int refCount = 1) // : RefCountable(refCount)
	{

	}

	virtual ~Job()
	{

	}
};

//Job�� OnExecute()�� ȣ���ϱ����� �Լ���ü 
struct ExecuteJobFunctor
{
	bool mIsExecute = true;

	void operator() (Job* job)
	{
		if (mIsExecute == true)
		{
			// job->OnExecute();
		}
	}
};
