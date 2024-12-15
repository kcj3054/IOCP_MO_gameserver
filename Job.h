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

//Job의 OnExecute()를 호출하기위한 함수객체 
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
